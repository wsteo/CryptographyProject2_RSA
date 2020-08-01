#include <fstream>
#include<iostream>
#include<cmath>
#include<cstdlib>
#include<cstring>
#include<conio.h>
#include<string>

using namespace std;

bool isPrime (long int n) {
    if (n < 2) return false;

    long int i = 2;

    while (i < n / 2) {
        if (n % i == 0) return false;
        i++;
    }

    return true;
}

bool isCoPrime (long int e, long int phi_n) {
    long int i = 2;
    while (i < e) {
        if ((e % i == 0) && (phi_n % i == 0)) return false;
        i++;
    }
    return true;
}

long int findE (long int phi_n) {
    long int e;
    do {
        cout << "Enter e value: ";
        cin >> e;
    } while (!isCoPrime (e, phi_n));
    return e;
}

long int findD (long int e, long int phi_n) {
    long int a =phi_n, b = e;
    long int x = 0, y = 1, u = 1, v = 0, m, n, q, r;
    long int gcd = b;

    while (a != 0) {
        q = gcd / a;
        r = gcd % a;
        m = x - u*q;
        n = y - v*q;
        gcd = a;
        a = r;
        x = u;
        y = v;
        u = m;
        v = n;
    }
    if (y < 1) {
        return phi_n + y;
    }

    return y;
}

void KeyGen (long int &e, long int &d, long int &n) {
    long int p, q;

    do {
        cout << "Enter a prime number (p): ";
        cin >> p;
    } while (!isPrime(p));

    do {
        cout << "Enter second prime number (q): ";
        cin >> q;
    } while (!isPrime(q));

    n = p * q;
    long int phi_n = (p-1) * (q-1);

    e = findE (phi_n);
    d = findD (e, phi_n);

    return;
}

void GenerateKey (long int &g, long int &f, long int &o) {
    long int p, q;

    do {
        cout << "Enter a prime number for second application (p): ";
        cin >> p;
    } while (!isPrime(p));

    do {
        cout << "Enter second prime number for second application (q): ";
        cin >> q;
    } while (!isPrime(q));

    o = p * q;
    long int phi_n = (p-1) * (q-1);

    g = findE (phi_n);
    f = findD (g, phi_n);

    return;
}

long int EncryptDecrypt (long int t, long int EorD, long int n) {
    long int rem;
    long int x = 1;
    long int plain = t;
    int counter=0;
    if(plain>n){
        while(plain>n){
            counter++;
            plain=plain-n;
        }
        while (EorD != 0) {
            rem = EorD % 2;
            EorD = EorD / 2;

            if (rem == 1) {
                x = (x * t) % n;
            }

            t = (t * t) % n;
        }

        return x+(n*counter);

    }else{
        while (EorD != 0) {
            rem = EorD % 2;
            EorD = EorD / 2;

            if (rem == 1) {
                x = (x * t) % n;
            }

            t = (t * t) % n;
        }
        return x;
    }
}

long int EncryptDecrypt2 (long int t, long int EorD, long int n) {
    long int rem;
    long int x = 1;

    while (EorD != 0) {
        rem = EorD % 2;
        EorD = EorD / 2;

        if (rem == 1) {
            x = (x * t) % n;
        }

        t = (t * t) % n;
    }

    return x;
}

long int EncryptInteger(long int c,long int e, long int d, long int n){

    //encrypt with public key
    long int C_ = EncryptDecrypt(c, e, n);
    //encrypt with private key
    long int C = EncryptDecrypt(C_, d, n);

    return C;
    /*
    //write on another file
    file.open("EncryptedText.txt");
    file<<C;
    file.close();
    //read from the previous file
    int content2;
    file.open("EncryptedText.txt");
    file>>content2;
    cout << "From EncryptedText File: " << content2 <<endl;
    file.close();

    //decrypt with private key
    long int M_ = EncryptDecrypt(content2, d, n);
    //decrypt with public key
    long int M = EncryptDecrypt(M_, e, n);

    //write to another file
    file.open("DecryptedText.txt");
    file<<M;
    file.close();

    cout << "Ciphertext: " << C << endl;
    cout << "Plaintext: " << M << endl;
    */
}

long int DecryptInteger(long int c,long int e, long int d, long int n){

    //decrypt with private key
    long int M_ = EncryptDecrypt(c, d, n);
    //decrypt with public key
    long int M = EncryptDecrypt(M_, e, n);

    return M;
}

void EncryptNumber(long int e, long int d, long int n){
    //open content from text file
    fstream file;
    long int content;

    file.open("PlainText.txt",ios::in);
    file>>content;
    cout << "From PlainText File: " << content << endl;
    file.close();

    //encrypt with public key
    long int C_ = EncryptDecrypt(content, e, n);
    //encrypt with private key
    long int C = EncryptDecrypt(C_, d, n);

    //write on another file
    file.open("EncryptedText.txt");
    file<<C;
    file.close();
    //read from the previous file

    cout << "Ciphertext: " << C << endl;
}

void DecryptNumber(long int e, long int d, long int n){
    fstream file;
    int content2;
    file.open("EncryptedText.txt");
    file>>content2;
    cout << "From EncryptedText File: " << content2 << endl;
    file.close();

    //decrypt with private key
    long int M_ = EncryptDecrypt(content2, d, n);
    //decrypt with public key
    long int M = EncryptDecrypt(M_, e, n);

    //write to another file
    file.open("DecryptedText.txt");
    file<<M;
    file.close();

    cout << "Decrypted Plain Text: " << M << endl;
}

void EncryptString(long int e, long int d, long int n){
    //open content from text file
    fstream file;
    char content[1000];
    int converted[1000];
    //int *C=new long int[1000];
    int C[1000];
    int M[1000];
    int counter=0;
    file.open("PlainTextString.txt",ios::in);
    while(file>>noskipws>>content){
        cout << "From PlainText File: " << content;
    }
    file.close();
    cout << endl;
    int sizearr=strlen(content);
    for(int i=0;i<sizearr;i++){
        counter++;
    }

    for(int i=0;i<counter;i++){
        converted[i] = (int)content[i];
        C[i] = EncryptInteger(converted[i],e,d,n);
        cout<<"Converted: "<<converted[i]<<endl;
        cout<<"Encrypted: "<<(char)C[i]<<endl;
    }

    file.open("EncryptedTextString.txt",ios::trunc|ios::out);
    for(int i=0;i<counter;i++){
        file<<(char)C[i];
    }
    file.close();


}

void DecryptString(long int e, long int d, long int n){
    fstream file;
    char content2[1000];
    //int *C=new long int[1000];
    int C[1000];
    int M[1000];
    int counter=0;

    file.open("EncryptedTextString.txt",ios::in);
    while(file>>noskipws>>content2){
        cout << "From EncryptedTextString File: " << content2;
    }
    file.close();
    cout << endl;
    int sizearr=strlen(content2);
    for(int i=0;i<sizearr;i++){
        counter++;
    }

    for(int i=0;i<counter;i++){
        cout<<"test: " << content2[i]<<endl;
    }

    cout<<"Decrypted: ";

    for(int i=0;i<counter;i++){
        //converted[i] = content[i];
        M[i] = DecryptInteger(content2[i],e,d,n);
        cout<<(char)M[i];
    }

   /* for(int j=0;j<counter;j++){
        M[j] = DecryptInteger(content[j],e,d,n);
        cout<<M[j]<<endl;
    }*/
    cout << endl;


    file.open("DecryptedTextString.txt",ios::trunc|ios::out);
    for(int i=0;i<counter;i++){
        file<<(char)M[i];
    }
}

int main()
{
    long int e, d, n;
    KeyGen(e, d, n);
    cout << "Public Key: (" << e << "," << n << ")" << endl;
    cout << "Private Key: (" << d << "," << n << ")" << endl;



    long int g, f, o;
    GenerateKey(g, f, o);
    cout << "Second Public Key: (" << g << "," << o << ")" << endl;
    cout << "Second Private Key: (" << f << "," << o << ")" << endl;

    cout << "1. Encrypt Number:\n2. Encrypt String:" << endl;
    int choice;
    cin >> choice;

    switch(choice){
        case 1:
            EncryptNumber(e,d,n);
            break;
        case 2:
            EncryptString(e,d,n);
            break;
        default:
            cout << "Invalid Option" << endl;
            exit(1);
    }

    cout << "1. Decrypt Number:\n2. Decrypt String:" << endl;
    int choice2;
    cin >> choice2;

    switch (choice2){
        case 1:
            DecryptNumber(g,f,o);
            break;
        case 2:
            DecryptString(g,f,o);
            break;
        default:
            cout << "Invalid Option" << endl;
            exit(1);
    }


    getch();

    return 0;
}
