#include <stdio.h>
#include <stdint.h>

uint8_t aesKey[16] = {0x01, 0x23, 0x45, 0x67, 0x89, 0xAB, 0xCD, 0xEF, 0xFE, 0xDC, 0xBA, 0x98, 0x76, 0x54, 0x32, 0x10};
uint8_t aesSBox[256] = {

};
void subBytes(uint8_t* state) {
}

void aesEncrypt(uint8_t* block, const uint8_t* key) {
}

int main() {
    uint8_t plaintext[16] = {0x48, 0x65, 0x6C, 0x6C, 0x6F, 0x2C, 0x20, 0x57, 0x6F, 0x72, 0x6C, 0x64, 0x21, 0x21, 0x21, 0x21};

    uint8_t ciphertext[16];
    aesEncrypt(plaintext, aesKey);

    printf("Plaintext: ");
    for (int i = 0; i < 16; i++) {
        printf("%02x", plaintext[i]);
    }
    printf("\n");

    printf("Ciphertext: ");
    for (int i = 0; i < 16; i++) {
        printf("%02x", ciphertext[i]);
    }
    printf("\n");

    return 0;
}
