#ifndef KEYGEN_H_INCLUDED
#define KEYGEN_H_INCLUDED

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

#endif // KEYGEN_H_INCLUDED
