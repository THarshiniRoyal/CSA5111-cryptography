#include <stdio.h>
#include <stdlib.h>

#define KEY_SIZE 3

int charToNum(char c) {
    return c - 'A';
}

char numToChar(int n) {
    return n + 'A';
}

int determinant(int mat[KEY_SIZE][KEY_SIZE]) {
    return mat[0][0] * (mat[1][1] * mat[2][2] - mat[1][2] * mat[2][1]) -
           mat[0][1] * (mat[1][0] * mat[2][2] - mat[1][2] * mat[2][0]) +
           mat[0][2] * (mat[1][0] * mat[2][1] - mat[1][1] * mat[2][0]);
}

int modInverse(int a) {
    for (int i = 1; i < 26; i++) {
        if ((a * i) % 26 == 1) {
            return i;
        }
    }
    return -1;
}

void matrixInverse(int mat[KEY_SIZE][KEY_SIZE], int inv[KEY_SIZE][KEY_SIZE]) {
    int det = determinant(mat);
    int detInverse = modInverse(det % 26);

    if (detInverse == -1) {
        printf("Matrix is not invertible. Hill cipher key cannot be determined.\n");
        return;
    }

    for (int i = 0; i < KEY_SIZE; i++) {
        for (int j = 0; j < KEY_SIZE; j++) {
            int cofactor = (mat[(j + 1) % KEY_SIZE][(i + 1) % KEY_SIZE] * mat[(j + 2) % KEY_SIZE][(i + 2) % KEY_SIZE] -
                            mat[(j + 1) % KEY_SIZE][(i + 2) % KEY_SIZE] * mat[(j + 2) % KEY_SIZE][(i + 1) % KEY_SIZE]);
            inv[i][j] = (cofactor * detInverse) % 26;
            if (inv[i][j] < 0) {
                inv[i][j] += 26;
            }
        }
    }
}

int main() {
    char knownPlaintext[KEY_SIZE][KEY_SIZE];
    char knownCiphertext[KEY_SIZE][KEY_SIZE];

    printf("Enter the known plaintext matrix (3x3):\n");
    for (int i = 0; i < KEY_SIZE; i++) {
        for (int j = 0; j < KEY_SIZE; j++) {
            scanf(" %c", &knownPlaintext[i][j]);
        }
    }

    printf("Enter the known ciphertext matrix (3x3):\n");
    for (int i = 0; i < KEY_SIZE; i++) {
        for (int j = 0; j < KEY_SIZE; j++) {
            scanf(" %c", &knownCiphertext[i][j]);
        }
    }

    int knownPlaintextMatrix[KEY_SIZE][KEY_SIZE];
    int knownCiphertextMatrix[KEY_SIZE][KEY_SIZE];

    for (int i = 0; i < KEY_SIZE; i++) {
        for (int j = 0; j < KEY_SIZE; j++) {
            knownPlaintextMatrix[i][j] = charToNum(knownPlaintext[i][j]);
            knownCiphertextMatrix[i][j] = charToNum(knownCiphertext[i][j]);
        }
    }

    int inversePlaintextMatrix[KEY_SIZE][KEY_SIZE];
    matrixInverse(knownPlaintextMatrix, inversePlaintextMatrix);

    if (determinant(knownPlaintextMatrix) == 0) {
        printf("Matrix is not invertible. Hill cipher key cannot be determined.\n");
        return 1;
    }

    int keyMatrix[KEY_SIZE][KEY_SIZE];
    for (int i = 0; i < KEY_SIZE; i++) {
        for (int j = 0; j < KEY_SIZE; j++) {
            keyMatrix[i][j] = 0;
            for (int k = 0; k < KEY_SIZE; k++) {
                keyMatrix[i][j] += (inversePlaintextMatrix[i][k] * knownCiphertextMatrix[k][j]) % 26;
            }
        }
    }

    printf("Hill cipher key matrix:\n");
    for (int i = 0; i < KEY_SIZE; i++) {
        for (int j = 0; j < KEY_SIZE; j++) {
            printf("%c ", numToChar(keyMatrix[i][j]));
        }
        printf("\n");
    }

    return 0;
}