def affine_caesar(text, a, b, encrypt=True):
    result = ""

    for char in text:
        if char.isalpha():
            shift = ord('A') if char.isupper() else ord('a')
            char_num = ord(char) - shift
            if encrypt:
                new_char_num = (a * char_num + b) % 26
            else:
                a_inverse = None
                for i in range(26):
                    if (a * i) % 26 == 1:
                        a_inverse = i
                        break
                if a_inverse is None:
                    return "Decryption not possible with this 'a' value."
                new_char_num = (a_inverse * (char_num - b)) % 26
            result += chr(new_char_num + shift)
        else:
            result += char

    return result

plaintext = input("Enter the text: ")
a = int(input("Enter the A value: "))
b = int(input("Enter the B value: "))

encrypted_text = affine_caesar(plaintext, a, b, encrypt=True)
print("Encrypted:", encrypted_text)

decrypted_text = affine_caesar(encrypted_text, a, b, encrypt=False)
print("Decrypted:", decrypted_text)
