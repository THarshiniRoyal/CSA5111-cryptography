def permute(data, table):
    return int(''.join(data[i] for i in table), 2)

def sdesF(r, k, s_box0, s_box1):
    ep_table = [3, 0, 1, 2, 1, 2, 3, 0]
    p4_table = [1, 3, 2, 0]
    ep = permute(r, ep_table)
    xor_result = bin(ep ^ k)[2:].zfill(8)
    s0_input = int(xor_result[:4], 2)
    s1_input = int(xor_result[4:], 2)
    s0_output = bin(s_box0[s0_input])[2:].zfill(2)
    s1_output = bin(s_box1[s1_input])[2:].zfill(2)
    p4_input = s0_output + s1_output
    return bin(int(r, 2) ^ int(permute(p4_input, p4_table), 2))[2:].zfill(4)

def generate_round_key(key, round):
    p8_table = [5, 2, 6, 3, 7, 4, 9, 8]
    key = permute(key, p8_table)
    shift = 1 if round == 1 else 3
    return int(bin((key << shift | key >> (10 - shift)) & 0x03FF)[2:], 2)

def sdes_encrypt(plaintext, key, iv, s_box0, s_box1):
    round_key1 = generate_round_key(key, 1)
    round_key2 = generate_round_key(key, 2)
    
    ep_table = [3, 0, 1, 2, 1, 2, 3, 0]
    p4_table = [1, 3, 2, 0]

    ep = permute(plaintext, ep_table)
    xor_result = bin(ep ^ round_key1)[2:].zfill(8)

    s0_input = int(xor_result[:4], 2)
    s1_input = int(xor_result[4:], 2)
    s0_output = bin(s_box0[s0_input])[2:].zfill(2)
    s1_output = bin(s_box1[s1_input])[2:].zfill(2)
    p4_input = s0_output + s1_output
    f_result = bin(int(plaintext, 2) ^ int(permute(p4_input, p4_table), 2))[2:].zfill(4)
    ciphertext = bin(int(iv, 2) ^ int(f_result, 2))[2:].zfill(12)

    ep = permute(ciphertext, ep_table)
    xor_result = bin(ep ^ round_key2)[2:].zfill(8)
    s0_input = int(xor_result[:4], 2)
    s1_input = int(xor_result[4:], 2)
    s0_output = bin(s_box0[s0_input])[2:].zfill(2)
    s1_output = bin(s_box1[s1_input])[2:].zfill(2)
    p4_input = s0_output + s1_output
    f_result = bin(int(ciphertext, 2) ^ int(permute(p4_input, p4_table), 2))[2:].zfill(4)
    ciphertext = bin(int(plaintext, 2) ^ int(f_result, 2))[2:].zfill(12)

    return ciphertext

def sdes_decrypt(ciphertext, key, iv, s_box0, s_box1):
    round_key1 = generate_round_key(key, 1)
    round_key2 = generate_round_key(key, 2)
    
    ep_table = [3, 0, 1, 2, 1, 2, 3, 0]
    p4_table = [1, 3, 2, 0]

    ep = permute(ciphertext, ep_table)
    xor_result = bin(ep ^ round_key2)[2:].zfill(8)
    s0_input = int(xor_result[:4], 2)
    s1_input = int(xor_result[4:], 2)
    s0_output = bin(s_box0[s0_input])[2:].zfill(2)
    s1_output = bin(s_box1[s1_input])[2:].zfill(2)
    p4_input = s0_output + s1_output
    f_result = bin(int(ciphertext, 2) ^ int(permute(p4_input, p4_table), 2))[2:].zfill(4)
    plaintext = bin(int(iv, 2) ^ int(f_result, 2))[2:].zfill(12)

    ep = permute(plaintext, ep_table)
    xor_result = bin(ep ^ round_key1)[2:].zfill(8)
    s0_input = int(xor_result[:4], 2)
    s1_input = int(xor_result[4:], 2)
    s0_output = bin(s_box0[s0_input])[2:].zfill(2)
    s1_output = bin(s_box1[s1_input])[2:].zfill(2)
    p4_input = s0_output + s1_output
    f_result = bin(int(plaintext, 2) ^ int(permute(p4_input, p4_table), 2))[2:].zfill(4)
    plaintext = bin(int(ciphertext, 2) ^ int(f_result, 2))[2:].zfill(12)

    return plaintext

def main():
    s_box0 = [1, 0, 3, 2, 3, 2, 1, 0, 0, 2, 1, 3, 3, 1, 3, 2]
    s_box1 = [0, 1, 2, 3, 2, 0, 1, 3, 3, 0, 1, 0, 2, 1, 0, 3]
    iv = '101010101010'
    key = '0111111101'
    plaintext = '000000010011'
    ciphertext = sdes_encrypt(plaintext, key, iv, s_box0, s_box1)
    print(f'Plaintext: {plaintext}')
    print(f'Key: {key}')
    print(f'IV: {iv}')
    print(f'Ciphertext: {ciphertext}')
    print(f'Decrypted: {sdes_decrypt(ciphertext, key, iv, s_box0, s_box1)}')

if __name__ == '__main__':
    main()
