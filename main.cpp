#include <iostream>

using namespace std;

bool isCoPrime(long int e,long int phi){
    long int i=2;
    while(i<e){
        if((e%i==0) && (phi%i==0)) return false;
        i++;
    }
    return true;
}

bool isPrime(long int n){
    if (n<2) return false;

    long int i = 2;

    while(i<n/2){
        if(n%i==0) return false;
        i++;
    }
    return true;
}

long int findE(long int phi){
    long int e;
    do{
        cout << "Input e value: ";
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
        return phi+y;
    }
    return y;
}

void KeyGen(long int &e, long int &d, long int &n){
    long int p,q; //prime numbers

    do{
        cout << "Enter Prime Number(p): ";
        cin >> p;
    }while (!isPrime(p));

    do{
        cout << "Enter Second Prime Number(q): ";
        cin >> q;
    }while (!isPrime(q));

    n=p*q;
    long int phi=(p-1)*(q-1);

    e=findE(phi);
    d=findD(e,phi);

    return;
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

int main()
{
    long int e,d,n;
    KeyGen(e,d,n);
    cout << "public key: ("<< e << ","<< n << ")" << endl;
    cout << "private key: ("<< d << ","<< n << ")" << endl;

    long int M = 95;
    long int C = EncryptDecrypt(M,e,n);
    long int M_= EncryptDecrypt(C,d,n);
    cout << "Ciphertext: " << C << " Plaintext: " << M_ << endl;

    return 0;
}
