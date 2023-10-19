  keys = [0x0F1571C947D9E859, 0x15A850C85E6933D2, 0x1590588B44D29C59, 0x15B8E17C7B9A8D9A, 0x1A082D7F9B05791E, 0x03463236DF480F33,
        0x0123456789ABCDEF, 0x1A3CD4B7B0C20DB0, 0x1A6388C02B7914DE, 0x133457799BBCDFF1, 0x022B8B08D94C4044, 0x10123456789ABCDEF,
        0x0123456789ABCDEF, 0x0A3CD4B7B0C20DB0, 0x06388C02B7914DE1, 0x33457799BBCDFF11, 0x22B8B08D94C40440]
def f_function(right_half, subkey):
    return right_half

def xor(a, b):
    return ''.join('1' if x != y else '0' for x, y in zip(a, b))

IP = [58, 50, 42, 34, 26, 18, 10, 2,
      60, 52, 44, 36, 28, 20, 12, 4,
      62, 54, 46, 38, 30, 22, 14, 6,
      64, 56, 48, 40, 32, 24, 16, 8,
      57, 49, 41, 33, 25, 17, 9, 1,
      59, 51, 43, 35, 27, 19, 11, 3,
      61, 53, 45, 37, 29, 21, 13, 5,
      63, 55, 47, 39, 31, 23, 15, 7]

IP_inverse = [40, 8, 48, 16, 56, 24, 64, 32,
              39, 7, 47, 15, 55, 23, 63, 31,
              38, 6, 46, 14, 54, 22, 62, 30,
              37, 5, 45, 13, 53, 21, 61, 29,
              36, 4, 44, 12, 52, 20, 60, 28,
              35, 3, 43, 11, 51, 19, 59, 27,
              34, 2, 42, 10, 50, 18, 58, 26,
              33, 1, 41, 9, 49, 17, 57, 25]
def des_decrypt(ciphertext, keys):
    plaintext = permute(ciphertext, IP)
    for key in keys[::-1]:
        left, right = plaintext[:32], plaintext[32:]
        new_right = f_function(right, key)
        new_left = xor(left, new_right)
        plaintext = right + new_left
    plaintext = plaintext[32:] + plaintext[:32]
    plaintext = permute(plaintext, IP_inverse)
    
    return plaintext
def permute(input_block, permutation_table):
    return ''.join(input_block[i - 1] for i in permutation_table)
ciphertext = "1000111100001110000111000010101010001100100100000011101110101100"
plaintext = des_decrypt(ciphertext, keys)
print("Decrypted Plaintext:", plaintext)
