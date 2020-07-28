#include <fstream>
#include<iostream>
#include<cmath>
#include<cstdlib>
#include<cstring>
#include<conio.h>

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

void EncryptNumber(long int e, long int d, long int n){

    //open content from text file
    fstream file;
    int content;
    file.open("PlainText.txt");
    file>>content;
    cout << "From PlainText File: " << content <<endl;
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
}

char* EncryptDecryptString (char content[], long int e, long int n)
{
    char *str = new char[1000];
    str=content;
    char *str1 = new char[1000];

    //cout << "Encrypting using Public Key: " << endl;
    int i = 0;
    while (i != strlen(str)) {
        str1[i] = EncryptDecrypt(str[i], e, n);
        i++;
    }

    //cout << str1 << endl;
    return str1;
}

void EncryptString(long int e, long int d, long int n){
    //open content from text file
    fstream file;
    char content[1000];
    char *C_=new char [1000];
    char *C=new char[1000];
    file.open("PlainTextString.txt",ios::in);
    file.getline(content,1000);
    cout << "From PlainText File: " << content <<endl;
    file.close();

    //encrypt with public key
    C_ = EncryptDecryptString(content, e, n);

    //cout<<"test: "<<C_;
    //encrypt with private key
    C = EncryptDecryptString(C_, d, n);
    //cout<<"test: "<<C;

    //write on another file
    file.open("EncryptedTextString.txt",ios::trunc|ios::out);
    file<<C;
    file.close();

    //read from the previous file
    char content2[1000];
    char *M_=new char [1000];
    char *M=new char[1000];
    file.open("EncryptedTextString.txt",ios::in);
    file.getline(content2,1000);
    cout << "From EncryptedText File: " << content2 <<endl;
    file.close();

    //decrypt with private key
    M_ = EncryptDecryptString(content2, d, n);
    //decrypt with public key
    M = EncryptDecryptString(M_, e, n);

    //write to another file
    file.open("DecryptedTextString.txt",ios::trunc|ios::out);
    file<<M;
    file.close();

    cout << "Ciphertext: " << C << endl;
    cout << "Plaintext: " << M << endl;
}

int main()
{
    long int e, d, n;
    KeyGen(e, d, n);
    cout << "Public Key: (" << e << "," << n << ")" << endl;
    cout << "Private Key: (" << d << "," << n << ")" << endl;

    cout << "\n1. Numbers: \n2. String: " << endl;
    int choice;
    cin >> choice;
    switch (choice){
        case 1:
            EncryptNumber(e,d,n);
            break;
        case 2:
            EncryptString(e,d,n);
            break;
        default:
            cout << "Invalid Choice. " << endl;
            exit(1);
    }



    return 0;
}
