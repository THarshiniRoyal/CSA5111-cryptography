#include <stdio.h>
#include <string.h>
#include <math.h>

int encrypt(char character, int e, int n) {
    return (int)pow(character - 'A', e) % n;
}

int main() {
    int e = 65537;
    int n = 104729;

    char plaintext[] = "HELLO";
    int ciphertext[strlen(plaintext)];

    for (int i = 0; i < strlen(plaintext); i++) {
        ciphertext[i] = encrypt(plaintext[i], e, n);
    }

    printf("Ciphertext: ");
    for (int i = 0; i < strlen(plaintext); i++) {
        printf("%d ", ciphertext[i]);
    }
    printf("\n");

    int frequency[26] = {0};

    for (int i = 0; i < strlen(plaintext); i++) {
        int decrypted_char = (int)pow(ciphertext[i], 1 / e) % n;
        frequency[decrypted_char] += 1;
    }

    printf("Frequency Analysis Attack Results:\n");
    for (int i = 0; i < 26; i++) {
        printf("%c (%d): %d times\n", i + 'A', i, frequency[i]);
    }

    return 0;
}
