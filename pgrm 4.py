def polyalphabetic_cipher(text, key):
    encrypted_text = ""
    key_length = len(key)
    for i in range(len(text)):
        char = text[i]
        if char.isalpha():
            shift = ord(key[i % key_length].lower()) - ord('a')
            if char.isupper():
                encrypted_char = chr(((ord(char) - ord('A') + shift) % 26) + ord('A'))
            else:
                encrypted_char = chr(((ord(char) - ord('a') + shift) % 26) + ord('a'))
        else:
            encrypted_char = char
        encrypted_text += encrypted_char
    return encrypted_text

message = input("Enter a message: ")
keyword = input("Enter a keyword: ")

encrypted_message = polyalphabetic_cipher(message, keyword)
print("Encrypted message:", encrypted_message)
