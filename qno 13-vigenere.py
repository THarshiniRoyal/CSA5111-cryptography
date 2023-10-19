import string

def vigenere(text, key_stream, decrypt=False):
    key_index = 0
    shift = -1 if decrypt else 1
    processed_text = ""
    for char in text:
        if char in string.ascii_uppercase:
            processed_char = chr(((ord(char) - ord('A') + shift * key_stream[key_index]) % 26) + ord('A'))
            key_index = (key_index + 1) % len(key_stream)
        else:
            processed_char = char
        processed_text += processed_char
    return processed_text
plaintext = "SEND MORE MONEY"
key_stream = [9, 0, 1, 7, 23, 15, 21, 14, 11, 11, 2, 8, 9]
encrypted_text = vigenere(plaintext, key_stream)
print("Encrypted Text (Part a):", encrypted_text)
ciphertext_b = encrypted_text
target_text_b = "CASH NOT NEEDED"
key_stream_b = [((ord(t) - ord('A') - ord(c) + ord('A')) % 26) for c, t in zip(ciphertext_b, target_text_b)]
decrypted_text_b = vigenere(ciphertext_b, key_stream_b, decrypt=True)
print("Decrypted Text (Part b):", decrypted_text_b)
