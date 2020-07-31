#include <fstream>
#include<iostream>
#include<cmath>
#include<cstdlib>
#include<cstring>
#include<conio.h>
#include<string>
#include<sstream>
#include <vector>
#include<string.h>

using namespace std;

bool isPrime (long int n) {
    if (n < 2) return false;

    long int i = 2;

    while (i <= n / 2) {
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

/*
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
*/

long int EncryptDecrypt (long int t, long int EorD, long int n) {
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
/*
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
*/
int EncryptInteger(long int c,long int e1, long int d2, long int n1, long int n2){

    //encrypt with public key
    long int C_ = EncryptDecrypt(c, e1, n1);
    //encrypt with private key
    long int C = EncryptDecrypt(C_, d2, n2);

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

int DecryptInteger(long int c,long int e2, long int d1, long int n1, long int n2){

    //decrypt with private key
    long int M_ = EncryptDecrypt(c, e2, n2);
    //decrypt with public key
    long int M = EncryptDecrypt(M_, d1, n1);
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

void EncryptString(long int e1, long int d1, long int n1,long int e2, long int d2, long int n2){
    //open content from text file
    fstream file;
    char content[1000];
    //int *C=new long int[1000];
    int C[1000];
    //int M[1000];
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
        //converted[i] = content[i];
        //C[i] = EncryptInteger(content[i],e1,d2,n1,n2);
        C[i] = EncryptInteger(content[i],e1,d2,n1,n2);
        //cout<<"Character: "<<content[i]<<endl;
        //cout<<"Plain: "<<(int)content[i]<<endl;
        cout<<"Encrypted: "<<C[i]<<endl;
    }

    file.open("EncryptedTextString.txt",ios::trunc|ios::out);
    for(int i=0;i<counter;i++){
        file<<C[i]<<",";
    }
    file.close();
}

void DecryptString(long int e1, long int d1, long int n1,long int e2, long int d2, long int n2){
    //open content from text file
    fstream file;
    char content[1000];
    //int *C=new long int[1000];
    //int C[1000];
    int M[1000];
    int counter=0;
    file.open("EncryptedTextString.txt",ios::in);
    while(file>>noskipws>>content){
        cout << "From EncryptedTextString File: " << content;
    }
    file.close();
    cout << endl;

    char *token = strtok(content,",");
    int contentArr[1000];

    int i = 0;
    while (token!=NULL){
        cout<<token<<endl;
        contentArr[i]=stoi(token); // convert string to int here
        token = strtok(NULL,",");
        i++;
    }

    cout<<"Decrypted: "<<endl;
    for(int j=0; j < i; j++){
        //cout<<contentArr[j]<<endl;
        M[j] = DecryptInteger(contentArr[j],e2,d1,n1,n2);
        cout<<M[j]<<endl;
        cout<<(char)M[j]<<endl;
    }

    file.open("DecryptedTextString.txt",ios::trunc|ios::out);
    for(int j=0;j<i;j++){
        file<<(char)M[j];
    }
    file.close();

    /*
    int sizearr=strlen(content);
    for(int i=0;i<sizearr;i++){
        counter++;
    }

    for(int i=0;i<counter;i++){
        //converted[i] = content[i];
        M[i] = DecryptInteger(content[i],e1,d2,n1,n2);
        //cout<<"Converted: "<<content[i]<<endl;
        cout<<"Decrypted: "<<M[i]<<endl;
    }

    file.open("DecryptedTextString.txt",ios::trunc|ios::out);
    for(int i=0;i<counter;i++){
        file<<(char)M[i]<<" ";
    }
    file.close();
    */
}

/*
DecryptString(long int e, long int d, long int n){
    fstream file;
    char content[1000];
    //int *C=new long int[1000];
    int C[1000];
    int M[1000];
    int counter=0;
    file.open("EncryptedTextString.txt",ios::in);
    while(file>>noskipws>>content){
        cout << "From EncryptedTextString File: " << content;
    }
    file.close();
    cout << endl;
    int sizearr=strlen(content);
    for(int i=0;i<sizearr;i++){
        counter++;
    }

    for(int i=0;i<counter;i++){
        cout<<"test: " << content[i]<<endl;
    }

    cout<<"Decrypted: ";

    for(int j=0;j<counter;j++){
        M[j] = DecryptInteger(content[j],e,d,n);
        cout<<(char)M[j];
    }
    cout << endl;


    file.open("DecryptedTextString.txt",ios::trunc|ios::out);
    for(int i=0;i<counter;i++){
        file<<(char)M[i];
    }
}
*/
int main()
{
    long int e1, d1, n1;
    cout << "First set" << endl;
    KeyGen(e1, d1, n1);
    cout << "Set 1" << endl;
    cout << "Public Key: (" << e1 << "," << n1 << ")" << endl;
    cout << "Private Key: (" << d1 << "," << n1 << ")" << endl;

    long int e2, d2, n2;
    cout << "Second set" << endl;
    KeyGen(e2, d2, n2);
    cout << "Set 2" << endl;
    cout << "Public Key: (" << e2 << "," << n2 << ")" << endl;
    cout << "Private Key: (" << d2 << "," << n2 << ")" << endl;

    cout << "1. Encrypt Number:\n2. Encrypt String:" << endl;
    int choice;
    cin >> choice;

    switch(choice){
        case 1:
            EncryptNumber(e1,d1,n1);
            break;
        case 2:
            EncryptString(e1,d1,n1,e2,d2,n2);
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
            //DecryptNumber(g,f,o);
            break;
        case 2:
            DecryptString(e1,d1,n1,e2,d2,n2);
            break;
        default:
            cout << "Invalid Option" << endl;
            exit(1);
    }

    getch();

    return 0;
}
