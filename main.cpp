#include <iostream>
#include<cmath>
#include<cstdlib>
#include<cstring>
#include<conio.h>

using namespace std;

bool isCoPrime(long int e,long int phi){
    long int lowest;
    long int i=2;
    bool coprime=true;

    if (phi>e){
        lowest=e;
    }else{
        lowest=phi;
    }

    while(i<lowest){
        if(!(phi%i) && !(e%i)){
            coprime=false;
        }
        i++;
    }
    return coprime;
}

bool isPrime(long int n){
    if (n<2) return false;

    long int i = 2;

    while(i<=n/2){
        if(!(n%i)) return false;
        i++;
    }
    return true;
}

long int findE(long int phi){
    long int e=0;
    do{
        cout << "Enter e value: ";
        cin >> e;
    }while (!isCoPrime (e,phi));
    return e;
}

long int findD(long int e, long int phi){
    long int a=phi,b=e;
    long int x=0,y=1,u=1,v=0,m,n,q,r;
    long int gcd=b;

    while(a!=0){
        q=gcd/a;
        r=gcd%a;
        m=x-u*q;
        n=y-v*q;
        gcd=a;
        a=r;
        x=u;
        y=v;
        u=m;
        v=n;
    }
    if(y<1){
        y=phi+y;
    }
    return y;
}

void KeyGen(long int &e, long int &d, long int &n){
    long int p,q,phi; //prime numbers

    do{
        cout << "Enter Prime Number(p): ";
        cin >> p;
    }while (!isPrime(p));

    do{
        cout << "Enter Second Prime Number(q): ";
        cin >> q;
    }while (!isPrime(q));

    n=p*q;
    cout << "n is " << n << endl;

    phi=(p-1)*(q-1);
    cout << "phi is " << phi << endl;

    e=findE(phi);
    cout << "e is " << e << endl;
    if(!e){
        cout << "Choose two suitable prime number" << endl;
        exit(1);
    }

    d=findD(e,phi);
    cout << "d is " << d << endl;
}

long int EncryptDecrypt(long int t, long int e_d, long int n){
    long int remainder;
    long int x=1;

    while(e_d != 0){
        remainder = e_d%2;
        e_d=e_d/2;

        if (remainder==1){
            x=(x*t)%n;
        }
        t=(t*t)%n; //increment
    }
    return x;
}

void EncryptDecryptString(long int e, long int n)
{
    char *str=new char[1000];
    char *str1=new char[1000];

    cout << "\nEnter a string: ";
    cin >> str;

    cout << "Encrypting using Public Key: " << endl;
    int i=0;
    while(i!=strlen(str)){
        str1[i]=EncryptDecrypt(str[i],e,n);
        i++;
    }
    cout << str1 << endl;
}

void EncryptDecryptNumber(long int num1, long int num2)
{
    long int n;

    cout << "\nEnter an integer number: ";
    cin >> n;

    cout << EncryptDecrypt(n,num1,num2) << endl;
}

int main()
{
    long int e,d=0,n;
    KeyGen(e,d,n);
    cout << "public key: ("<< e << ","<< n << ")" << endl;
    cout << "private key: ("<< d << ","<< n << ")" << endl;

    cout << "\nPress 1: Encrypt Numbers" << "\nPress 2: Encrypt String" <<endl;
    int choice;
    cin >> choice;

    switch (choice){
        case 1:
            EncryptDecryptNumber(e,n);
            break;
        case 2:
            EncryptDecryptString(e,n);
            break;
        default:
            cout<<"Invalid option"<<endl;
            exit(1);
    }

    cout << "\nPress 1: Decrypt Numbers" << "\nPress 2: Decrypt String" <<endl;

    switch (choice){
        case 1:
            EncryptDecryptNumber(d,n);
            break;
        case 2:
            EncryptDecryptString(d,n);
            break;
        default:
            cout<<"Invalid Option"<<endl;
            exit(1);
    }
    getch();
    return 0;
}
