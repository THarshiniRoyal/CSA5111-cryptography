#include <stdio.h>

int pc1[] = {
    57, 49, 41, 33, 25, 17, 9,
    1, 58, 50, 42, 34, 26, 18,
    10, 2, 59, 51, 43, 35, 27,
    19, 11, 3, 60, 52, 44, 36,
    63, 55, 47, 39, 31, 23, 15,
    7, 62, 54, 46, 38, 30, 22,
    14, 6, 61, 53, 45, 37, 29,
    21, 13, 5, 28, 20, 12, 4
};

int shiftBits[] = {
    1, 1, 2, 2, 2, 2, 2, 2,
    1, 2, 2, 2, 2, 2, 2, 1
};

int pc2[] = {
    14, 17, 11, 24, 1, 5,
    3, 28, 15, 6, 21, 10,
    23, 19, 12, 4, 26, 8,
    16, 7, 27, 20, 13, 2,
    41, 52, 31, 37, 47, 55,
    30, 40, 51, 45, 33, 48,
    44, 49, 39, 56, 34, 53,
    46, 42, 50, 36, 29, 32
};

void generateSubKey(unsigned long long key) {
    unsigned long long permutedKey = 0;
    for (int i = 0; i < 56; i++) {
        int bitPos = pc1[i] - 1;
        permutedKey |= ((key >> (64 - bitPos)) & 1) << (55 - i);
    }

    unsigned int C0 = (permutedKey >> 28) & 0xFFFFFFF;
    unsigned int D0 = permutedKey & 0xFFFFFFF;

    for (int round = 0; round < 16; round++) {
        int shift = shiftBits[round];
        C0 = ((C0 << shift) | (C0 >> (28 - shift))) & 0xFFFFFFF;
        D0 = ((D0 << shift) | (D0 >> (28 - shift))) & 0xFFFFFFF;

        unsigned long long combinedCD = ((unsigned long long)C0 << 28) | D0;
        unsigned long long subKey = 0;
        for (int i = 0; i < 48; i++) {
            int bitPos = pc2[i] - 1;
            subKey |= ((combinedCD >> (56 - bitPos)) & 1) << (47 - i);
        }

        printf("Round %2d: 0x%012llx\n", round + 1, subKey);
    }
}

int main() {
    unsigned long long initialKey;
    printf("Enter the initial key (64-bit in hexadecimal): ");
    scanf("%llx", &initialKey);

    printf("Subkeys:\n");
    generateSubKey(initialKey);

    return 0;
}
