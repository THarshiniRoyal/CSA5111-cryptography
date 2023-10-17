def caesar_cipher(text, shift):
    result = ""
    for char in text:
        if char.isalpha():
            offset = 65 if char.isupper() else 97
            shifted_char = chr((ord(char) - offset + shift) % 26 + offset)
            result += shifted_char
        else:
            result += char
    return result

text = input("Enter the text: ")
shift = int(input("Enter the shift value (1-25): "))

if 1 <= shift <= 25:
    encrypted_text = caesar_cipher(text, shift)
    decrypted_text = caesar_cipher(encrypted_text, -shift)
    print(f"Encrypted text: {encrypted_text}")
    print(f"Decrypted text: {decrypted_text}")
else:
    print("Shift value must be between 1 and 25.")
