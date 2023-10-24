#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int gcd(int a, int b) {
    if (b == 0)
        return a;
    return gcd(b, a % b);
}
int mod_inverse(int a, int m) {
    int m0 = m;
    int x0 = 0, x1 = 1;
    int q, t;

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
    int p = 61;
    int q = 53; 

    int n = p * q; 
    int phi = (p - 1) * (q - 1);

    int e = 17; 
    int d = mod_inverse(e, phi); 
    printf("Public key (e, n): (%d, %d)\n", e, n);
    printf("Private key (d, n): (%d, %d)\n", d, n);
    int plaintext = 42;
    int ciphertext = (int)pow(plaintext, e) % n;
    int decrypted = (int)pow(ciphertext, d) % n;

    printf("Plaintext: %d\n", plaintext);
    printf("Ciphertext: %d\n", ciphertext);
    printf("Decrypted: %d\n", decrypted);

    return 0;
}
