def generate_cipher(keyword):
    keyword = ''.join(sorted(set(keyword.upper()), key=keyword.upper().index))
    return keyword + ''.join(filter(str.isalpha, 'ABCDEFGHIJKLMNOPQRSTUVWXYZ'))

def monoalphabetic_cipher(text, cipher_sequence):
    return ''.join(cipher_sequence[ord(char) - ord('A')] if char.isalpha() else char for char in text.upper())

keyword = input("Enter the keyword: ")
cipher_sequence = generate_cipher(keyword)
plaintext = input("Enter the plaintext: ")
encrypted_text = monoalphabetic_cipher(plaintext, cipher_sequence)
print("Cipher Sequence:", cipher_sequence)
print("Encrypted Text:", encrypted_text)
