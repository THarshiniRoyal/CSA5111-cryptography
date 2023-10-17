import numpy as np

def prepare_message(message, block_size):
    message = message.replace(" ", "").upper()
    while len(message) % block_size != 0:
        message += 'X'
    return message
def hill_cipher_encrypt(message, key_matrix):
    message = prepare_message(message, 2)
    key_matrix = np.array(key_matrix)
    cipher_text = ""
    block_size = 2

    for i in range(0, len(message), block_size):
        block = message[i:i+block_size]
        block_vector = np.array([ord(c) - ord('A') for c in block])
        encrypted_vector = np.dot(key_matrix, block_vector) % 26
        encrypted_block = ''.join([chr(v + ord('A')) for v in encrypted_vector])
        cipher_text += encrypted_block

    return cipher_text

def hill_cipher_decrypt(cipher_text, key_matrix):
    key_matrix = np.array(key_matrix)
    key_matrix_inverse = np.linalg.inv(key_matrix)
    key_matrix_inverse = (key_matrix_inverse * np.linalg.det(key_matrix)).round()
    key_matrix_inverse = key_matrix_inverse.astype(int) % 26
    plain_text = ""
    block_size = 2

    for i in range(0, len(cipher_text), block_size):
        block = cipher_text[i:i+block_size]
        block_vector = np.array([ord(c) - ord('A') for c in block])
        decrypted_vector = np.dot(key_matrix_inverse, block_vector) % 26
        decrypted_block = ''.join([chr(v + ord('A')) for v in decrypted_vector])
        plain_text += decrypted_block
    return plain_text
key_matrix = [
    [9, 4],
    [5, 7]
]

message = "meet me at the usual place at ten rather than eight oclock"
cipher_text = hill_cipher_encrypt(message, key_matrix)
print("Encrypted message:", cipher_text)
decrypted_message = hill_cipher_decrypt(cipher_text, key_matrix)
print("Decrypted message:", decrypted_message)
