#include <stdio.h>

unsigned short permute(unsigned short data, unsigned short* table, int size) {
    unsigned short result = 0;
    for (int i = 0; i < size; i++) {
        result <<= 1;
        result |= (data >> (7 - table[i])) & 0x01;
    }
    return result;
}

unsigned short sdesF(unsigned short r, unsigned short k, unsigned short* sBox0, unsigned short* sBox1) {
    unsigned short epTable[] = {3, 0, 1, 2, 1, 2, 3, 0};
    unsigned short p4Table[] = {1, 3, 2, 0};
    unsigned short ep = permute(r, epTable, 8);
    unsigned short xorResult = ep ^ k;
    unsigned short s0Input = (xorResult & 0xF000) >> 12;
    unsigned short s1Input = (xorResult & 0x0F00) >> 8;
    unsigned short s0Output = sBox0[s0Input >> 2 + s0Input & 0x03];
    unsigned short s1Output = sBox1[s1Input >> 2 + s1Input & 0x03];
    unsigned short p4Input = (s0Output << 2) | s1Output;
    return r ^ permute(p4Input, p4Table, 4);
}

unsigned short generateRoundKey(unsigned short key, int round) {
    unsigned short p8Table[] = {5, 2, 6, 3, 7, 4, 9, 8};
    key = permute(key, p8Table, 10);
    int shift = (round == 1) ? 1 : 3;
    return ((key << shift) | (key >> (10 - shift))) & 0x03FF;
}

unsigned short sdesEncrypt(unsigned short plaintext, unsigned short key, unsigned short iv, unsigned short* sBox0, unsigned short* sBox1) {
    unsigned short ciphertext = 0;
    unsigned short roundKey1 = generateRoundKey(key, 1);
    unsigned short roundKey2 = generateRoundKey(key, 2);

    unsigned short epTable[] = {3, 0, 1, 2, 1, 2, 3, 0};
    unsigned short p4Table[] = {1, 3, 2, 0};

    unsigned short ep = permute(plaintext, epTable, 8);
    unsigned short xorResult = ep ^ roundKey1;

    unsigned short s0Input = (xorResult & 0xF000) >> 12;
    unsigned short s1Input = (xorResult & 0x0F00) >> 8;
    unsigned short s0Output = sBox0[s0Input >> 2 + s0Input & 0x03];
    unsigned short s1Output = sBox1[s1Input >> 2 + s1Input & 0x03];
    unsigned short p4Input = (s0Output << 2) | s1Output;
    unsigned short fResult = plaintext ^ permute(p4Input, p4Table, 4);
    ciphertext = (iv ^ fResult) & 0x0FFF;

    ep = permute(ciphertext, epTable, 8);
    xorResult = ep ^ roundKey2;
    s0Input = (xorResult & 0xF000) >> 12;
    s1Input = (xorResult & 0x0F00) >> 8;
    s0Output = sBox0[s0Input >> 2 + s0Input & 0x03];
    s1Output = sBox1[s1Input >> 2 + s1Input & 0x03];
    p4Input = (s0Output << 2) | s1Output;
    fResult = ciphertext ^ permute(p4Input, p4Table, 4);
    ciphertext = (plaintext ^ fResult) & 0x0FFF;

    return ciphertext;
}

unsigned short sdesDecrypt(unsigned short ciphertext, unsigned short key, unsigned short iv, unsigned short* sBox0, unsigned short* sBox1) {
    unsigned short plaintext = 0;
    unsigned short roundKey1 = generateRoundKey(key, 1);
    unsigned short roundKey2 = generateRoundKey(key, 2);

    unsigned short epTable[] = {3, 0, 1, 2, 1, 2, 3, 0};
    unsigned short p4Table[] = {1, 3, 2, 0};

    unsigned short ep = permute(ciphertext, epTable, 8);
    unsigned short xorResult = ep ^ roundKey2;
    unsigned short s0Input = (xorResult & 0xF000) >> 12;
    unsigned short s1Input = (xorResult & 0x0F00) >> 8;
    unsigned short s0Output = sBox0[s0Input >> 2 + s0Input & 0x03];
    unsigned short s1Output = sBox1[s1Input >> 2 + s1Input & 0x03];
    unsigned short p4Input = (s0Output << 2) | s1Output;
    unsigned short fResult = ciphertext ^ permute(p4Input, p4Table, 4);
    plaintext = (iv ^ fResult) & 0x0FFF;

    ep = permute(plaintext, epTable, 8);
    xorResult = ep ^ roundKey1;
    s0Input = (xorResult & 0xF000) >> 12;
    s1Input = (xorResult & 0x0F00) >> 8;
    s0Output = sBox0[s0Input >> 2 + s0Input & 0x03];
    s1Output = sBox1[s1Input >> 2 + s1Input & 0x03];
    p4Input = (s0Output << 2) | s1Output;
    fResult = plaintext ^ permute(p4Input, p4Table, 4);
    plaintext = (ciphertext ^ fResult) & 0x0FFF;

    return plaintext;
}

void displayBinary(unsigned short data) {
    for (int i = 11; i >= 0; i--) {
        printf("%d", (data >> i) & 0x01);
    }
    printf("\n");
}

int main() {
    unsigned short sBox0[] = {1, 0, 3, 2, 3, 2, 1, 0, 0, 2, 1, 3, 3, 1, 3, 2};
    unsigned short sBox1[] = {0, 1, 2, 3, 2, 0, 1, 3, 3, 0, 1, 0, 2, 1, 0, 3};
    unsigned short iv = 0b101010101010, key = 0b0111111101, plaintext = 0b000000010011;
    unsigned short ciphertext = sdesEncrypt(plaintext, key, iv, sBox0, sBox1);
    printf("Plaintext: ");
    displayBinary(plaintext);
    printf("Key: ");
    displayBinary(key);
    printf("IV: ");
    displayBinary(iv);
    printf("Ciphertext: ");
    displayBinary(ciphertext);
    printf("Decrypted: ");
    displayBinary(sdesDecrypt(ciphertext, key, iv, sBox0, sBox1));
    return 0;
}
