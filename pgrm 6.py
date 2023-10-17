def break_affine_cipher(c, a, b):
    return ''.join([chr((a * (ord(x) - 65 - b) % 26) + 97) if x.isalpha() else x for x in c])

ciphertext = input("Enter the ciphertext: ").upper()
most_common = 'B'
second_most_common = 'U'
a = (ord(most_common) - ord(second_most_common)) % 26
b = (ord(most_common) - ord('A')) % 26
plaintext = break_affine_cipher(ciphertext, a, b)
print(plaintext)
