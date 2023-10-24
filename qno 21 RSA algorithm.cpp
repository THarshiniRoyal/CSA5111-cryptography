#include <stdio.h>
int gcd(int a, int b) {
    if (b == 0)
        return a;
    return gcd(b, a % b);
}

int main() {
    int n = 77;
    int e = 7; 
    int ciphertext = 14; 
    int p = 7; 
    int q = 11; 
    int phi_n = (p - 1) * (q - 1);
    int d = 1;
    while ((d * e) % phi_n != 1) {
        d++;
    }
    int decrypted = 1;
    for (int i = 0; i < d; i++) {
        decrypted = (decrypted * ciphertext) % n;
    }

    printf("Ciphertext: %d\n", ciphertext);
    printf("Decrypted plaintext: %d\n", decrypted);

    return 0;
}
