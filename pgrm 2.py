def mono_substitution_cipher(text, key):
    cipher = str.maketrans('abcdefghijklmnopqrstuvwxyz', key)
    return text.translate(cipher)

key = 'zyxwvutsrqponmlkjihgfedcba'  
plaintext = input("Enter the text to encrypt: ")
encrypted_text = mono_substitution_cipher(plaintext, key)
print(f"Encrypted text: {encrypted_text}")
