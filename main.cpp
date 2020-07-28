#include <iostream>
#include <fstream>

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

void GenerateKey (long int &e, long int &d, long int &n) {
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

int main()
{
    long int e, d, n;
    GenerateKey(e, d, n);
    cout << "Public Key: (" << e << "," << n << ")" << endl;
    cout << "Private Key: (" << d << "," << n << ")" << endl;

    fstream file;
    int content;
    file.open("PlainText.txt");
    file>>content;
    cout << "From PlainText File: " << content <<endl;
    file.close();

    long int C_ = EncryptDecrypt(content, e, n);
    long int C = EncryptDecrypt(C_, d, n);

    file.open("EncryptedText.txt");
    file<<C;
    file.close();

    int content2;
    file.open("EncryptedText.txt");
    file>>content2;
    cout << "From EncryptexText File: " << content2 <<endl;
    file.close();

    long int M_ = EncryptDecrypt(content2, d, n);
    long int M = EncryptDecrypt(M_, e, n);

    file.open("DecryptedText.txt");
    file<<M;
    file.close();

    cout << "Ciphertext: " << C << " Plaintext: " << M << endl;

    return 0;
}
