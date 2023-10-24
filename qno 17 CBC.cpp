#include <stdio.h>
#include <string.h>
unsigned char des3Key[24] = {
    0x01, 0x23, 0x45, 0x67, 0x89, 0xab, 0xcd, 0xef,
    0xfe, 0xdc, 0xba, 0x98, 0x76, 0x54, 0x32, 0x10,
    0x01, 0x23, 0x45, 0x67, 0x89, 0xab, 0xcd, 0xef
};
unsigned char iv[8] = {0x12, 0x34, 0x56, 0x78, 0x90, 0xab, 0xcd, 0xef};
void generateKeySchedule(unsigned char* key) {
}
void encrypt3DES(unsigned char* plaintext, unsigned char* ciphertext) {
}
int main() {
    unsigned char plaintext[] = "Hello, World!";
    unsigned char ciphertext[1024];
    printf("Encrypted Text: ");
    for (int i = 0; i < strlen((char *)plaintext); i++) {
        printf("%02x", ciphertext[i]);
    }
    printf("\n");

    return 0;
}
