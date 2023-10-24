#include <stdio.h>
#include <math.h>
unsigned long long mod_pow(unsigned long long base, unsigned long long exponent, unsigned long long modulus) {
    unsigned long long result = 1;
    while (exponent > 0) {
        if (exponent % 2 == 1) {
            result = (result * base) % modulus;
        }
        base = (base * base) % modulus;
        exponent /= 2;
    }
    return result;
}

int main() {
    unsigned long long g = 5; 
    unsigned long long p = 23;
    unsigned long long alice_private_key = 6;
    unsigned long long bob_private_key = 15;
    unsigned long long alice_public_key = mod_pow(g, alice_private_key, p);
    unsigned long long bob_public_key = mod_pow(g, bob_private_key, p);
    unsigned long long alice_shared_secret = mod_pow(bob_public_key, alice_private_key, p);
    unsigned long long bob_shared_secret = mod_pow(alice_public_key, bob_private_key, p);
    printf("Alice's Shared Secret: %llu\n", alice_shared_secret);
    printf("Bob's Shared Secret: %llu\n", bob_shared_secret);

    return 0;
}
