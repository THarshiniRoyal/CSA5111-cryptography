import string
from collections import Counter
def decrypt_additive(ciphertext, key):
    return ''.join([chr(((ord(c) - ord('A') - key) % 26) + ord('A')) if c in string.ascii_uppercase else c for c in ciphertext])
def letter_frequency_attack(ciphertext, top_n=10):
    ciphertext_freq = Counter(ciphertext.upper())
    possible_plaintexts = []
    for key in range(26):
        decrypted_text = decrypt_additive(ciphertext, key)
        decrypted_freq = Counter(decrypted_text.upper())
        likelihood = sum(ciphertext_freq[char] * decrypted_freq[char] for char in string.ascii_uppercase)
        possible_plaintexts.append((decrypted_text, likelihood))

    return sorted(possible_plaintexts, key=lambda x: x[1], reverse=True)[:top_n]
ciphertext = "WKLVLV DV D WHVWHUB VWUHDWHFWPH"
top_possible_plaintexts = letter_frequency_attack(ciphertext, top_n=10)

for i, (plaintext, likelihood) in enumerate(top_possible_plaintexts):
    print(f"Possible Plaintext {i + 1}: {plaintext} (Likelihood: {likelihood})")
