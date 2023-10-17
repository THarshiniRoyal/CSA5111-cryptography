def create_matrix(key):
    key = key.upper().replace("J", "I") + "ABCDEFGHIKLMNOPQRSTUVWXYZ"
    matrix = []

    for char in key:
        if char not in matrix:
            matrix.append(char)

    return matrix

def playfair_cipher(key, text):
    matrix = create_matrix(key)
    text = text.upper().replace("J", "I").replace(" ", "")
    cipher = []

    for i in range(0, len(text), 2):
        c1, c2 = text[i], text[i + 1] if i + 1 < len(text) else 'X'
        r1, c1 = divmod(matrix.index(c1), 5)
        r2, c2 = divmod(matrix.index(c2), 5)

        if r1 == r2:
            cipher.append(matrix[r1 * 5 + (c1 + 1) % 5])
            cipher.append(matrix[r2 * 5 + (c2 + 1) % 5])
        elif c1 == c2:
            cipher.append(matrix[(r1 + 1) % 5 * 5 + c1])
            cipher.append(matrix[(r2 + 1) % 5 * 5 + c2])
        else:
            cipher.append(matrix[r1 * 5 + c2])
            cipher.append(matrix[r2 * 5 + c1])

    return ''.join(cipher)

key = input("Keyword: ")
text = input("Text: ")
print("Cipher: " + playfair_cipher(key, text))
