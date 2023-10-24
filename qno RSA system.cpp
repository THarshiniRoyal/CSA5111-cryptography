#include <stdio.h>

int gcd(int a, int b) {
    if (b == 0)
        return a;
    return gcd(b, a % b);
}

int multiplicativeInverse(int a, int m) {
    int m0 = m, t, q;
    int x0 = 0, x1 = 1;

    while (a > 1) {
        q = a / m;
        t = m;
        m = a % m;
        a = t;
        t = x0;
        x0 = x1 - q * x0;
        x1 = t;
    }

    if (x1 < 0)
        x1 += m0;

    return x1;
}

int main() {
    int e, n;
    printf("Enter the public key (e): ");
    scanf("%d", &e);
    printf("Enter the modulus (n): ");
    scanf("%d", &n);

    int p, q;
    for (p = 2; p < n; p++) {
        if (n % p == 0) {
            q = n / p;
            break;
        }
    }

    int phi = (p - 1) * (q - 1);
    int d = multiplicativeInverse(e, phi);

    printf("Private key (d): %d\n", d);

    return 0;
}
