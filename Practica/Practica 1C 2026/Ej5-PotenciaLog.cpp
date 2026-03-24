#include <vector>
#include <iostream>
#include <queue>
#include <list>
#include <unordered_set>
#include <map>
#include <unordered_map>
#include <cstdio>
using namespace std;


#include <iostream>
using namespace std;

long long pow10ll(int k) {
    long long p = 1;
    while (k--) p *= 10;
    return p;
}

int digits(long long x) {
    if (x == 0) return 1;
    int d = 0;
    while (x > 0) {
        x /= 10;
        d++;
    }
    return d;
}

long long karatsuba(long long a, long long b) {
    // Caso base
    if (a < 10 || b < 10) return a * b;

    int n = max(digits(a), digits(b));
    int m = n / 2;

    long long p = pow10ll(m);

    long long a1 = a / p;
    long long a0 = a % p;
    long long b1 = b / p;
    long long b0 = b % p;

    long long z2 = karatsuba(a1, b1);
    long long z0 = karatsuba(a0, b0);
    long long z1 = karatsuba(a1 + a0, b1 + b0) - z2 - z0;

    return z2 * pow10ll(2 * m) + z1 * p + z0;
}

long long potencia(long long a, long long b) {
    if (b == 0) return 1;
    if (b == 1) return a;

    long long half = potencia(a, b / 2);

    if (b % 2 == 0) {
        return half * half;
    } else {
        return a * half * half;
    }
}

int main() {
    cout << "Pruebas de potencia(a, b):\n";

    cout << "2^0  = " << potencia(2, 0) << "  (esperado: 1)\n";
    cout << "2^10 = " << potencia(2, 10) << " (esperado: 1024)\n";
    cout << "3^5  = " << potencia(3, 5) << "  (esperado: 243)\n";
    cout << "5^4  = " << potencia(5, 4) << "  (esperado: 625)\n";
    cout << "10^6 = " << potencia(10, 6) << " (esperado: 1000000)\n";

    // Si queres seguir probando Karatsuba, descomenta estas lineas.
    // long long a = 1234, b = 5678;
    // cout << "Karatsuba: " << karatsuba(a, b) << " (esperado: 7006652)\n";

    return 0;
}