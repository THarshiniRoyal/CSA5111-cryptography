def playfair_encrypt(key, message):
    key = key.replace("J", "I")
    key_square = []
    for letter in key:
        if letter not in key_square:
            key_square.append(letter)
    for letter in "ABCDEFGHIKLMNOPQRSTUVWXYZ":
        if letter not in key_square:
            key_square.append(letter)
    message = message.upper().replace("J", "I")
    message = "".join(filter(str.isalpha, message))
    digraphs = []
    i = 0
    while i < len(message):
        if i == len(message) - 1 or message[i] == message[i+1]:
            digraphs.append(message[i] + "X")
            i += 1
        else:
            digraphs.append(message[i:i+2])
            i += 2
    ciphertext = ""
    for digraph in digraphs:
        row1, col1 = divmod(key_square.index(digraph[0]), 5)
        row2, col2 = divmod(key_square.index(digraph[1]), 5)
        if row1 == row2:
            ciphertext += key_square[row1*5 + (col1+1)%5] + key_square[row2*5 + (col2+1)%5]
        elif col1 == col2:
            ciphertext += key_square[((row1+1)%5)*5 + col1] + key_square[((row2+1)%5)*5 + col2]
        else:
            ciphertext += key_square[row1*5 + col2] + key_square[row2*5 + col1]
    return ciphertext
key = "MFHIKUNOPQZVWXYELARGDSTBC"
message = "Must see you over Cadogan West. Coming at once"
ciphertext = playfair_encrypt(key, message)
print(ciphertext)
