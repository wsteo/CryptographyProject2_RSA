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
        cout << "Put e value: ";
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
        cout << "Put a prime number: ";
        cin >> p;
    } while (!isPrime(p));

    do {
        cout << "Put a prime number: ";
        cin >> q;
    } while (!isPrime(q));

    n = p * q;
    long int phi_n = (p-1) * (q-1);

    e = findE (phi_n);
    d = findD (e, phi_n);

    return;
}

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

int EncryptNumber(long int c,long int e, long int d, long int n){

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

int DecryptNumber(long int c,long int e, long int d, long int n){

    //decrypt with private key
    long int M_ = EncryptDecrypt(c, d, n);
    //decrypt with public key
    long int M = EncryptDecrypt(M_, e, n);
    return M;
}


void EncryptString(long int e, long int d, long int n){
    //open content from text file
    fstream file;
    char content[1000];
    //int *C=new long int[1000];
    int C[1000];
    int M[1000];
    file.open("PlainTextString.txt",ios::in);
    file.getline(content,1000);
    cout << "From PlainText File: " << content <<endl;
    file.close();

    int i;
    int converted[100];
    for(i=0;i<3;i++){
        converted[i] = content[i];
        C[i] = EncryptNumber(converted[i],e,d,n);
        cout<<"Converted: "<<converted[i]<<endl;
        cout<<"Encrypted_1: "<<C[i]<<endl;
    }

    for(i=0;i<3;i++){
        M[i] = DecryptNumber(C[i],e,d,n);
        cout<<"Decrypted_1: "<<(char)M[i]<<endl;
    }

    file.open("EncryptedTextString.txt");
    for(i=0;i<3;i++){
        file<<to_string(C[i])+" ";
    }
    file.close();
}

int main()
{
    long int e, d, n;
    KeyGen(e, d, n);
    cout << "Public Key: (" << e << "," << n << ")" << endl;
    cout << "Private Key: (" << d << "," << n << ")" << endl;

    EncryptString(e,d,n);




    return 0;
}
