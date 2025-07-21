BLOCK_SIZE = 4

def encrypt_block(block, key):
    return bytes([(b + key) % 256 for b in block])

def decrypt_block(block, key):
    return bytes([(b - key) % 256 for b in block])

def xor_bytes(a, b):
    return bytes([x ^ y for x, y in zip(a, b)])

def pad(data):
    padding_len = BLOCK_SIZE - len(data) % BLOCK_SIZE
    return data + bytes([0] * padding_len)

def unpad(data):
    return data.rstrip(b'\x00')



def encrypt_ecb(plaintext, key):
    plaintext = pad(plaintext)
    ciphertext = b''
    for i in range(0, len(plaintext), BLOCK_SIZE):
        block = plaintext[i:i+BLOCK_SIZE]
        ciphertext += encrypt_block(block, key)
    return ciphertext

def decrypt_ecb(ciphertext, key):
    plaintext = b''
    for i in range(0, len(ciphertext), BLOCK_SIZE):
        block = ciphertext[i:i+BLOCK_SIZE]
        plaintext += decrypt_block(block, key)
    return unpad(plaintext)




def encrypt_cbc(plaintext, key, iv):
    plaintext = pad(plaintext)
    ciphertext = b''
    prev = iv
    for i in range(0, len(plaintext), BLOCK_SIZE):
        block = xor_bytes(plaintext[i:i+BLOCK_SIZE], prev)
        enc = encrypt_block(block, key)
        ciphertext += enc
        prev = enc
    return ciphertext

def decrypt_cbc(ciphertext, key, iv):
    plaintext = b''
    prev = iv
    for i in range(0, len(ciphertext), BLOCK_SIZE):
        block = ciphertext[i:i+BLOCK_SIZE]
        dec = decrypt_block(block, key)
        plaintext += xor_bytes(dec, prev)
        prev = block
    return unpad(plaintext)




def encrypt_cfb(plaintext, key, iv):
    plaintext = pad(plaintext)
    ciphertext = b''
    feedback = iv
    for i in range(0, len(plaintext), BLOCK_SIZE):
        enc = encrypt_block(feedback, key)
        cipher_block = xor_bytes(plaintext[i:i+BLOCK_SIZE], enc)
        ciphertext += cipher_block
        feedback = cipher_block
    return ciphertext

def decrypt_cfb(ciphertext, key, iv):
    plaintext = b''
    feedback = iv
    for i in range(0, len(ciphertext), BLOCK_SIZE):
        enc = encrypt_block(feedback, key)
        plain_block = xor_bytes(ciphertext[i:i+BLOCK_SIZE], enc)
        plaintext += plain_block
        feedback = ciphertext[i:i+BLOCK_SIZE]
    return unpad(plaintext)


def encrypt_ofb(plaintext, key, iv):
    plaintext = pad(plaintext)
    ciphertext = b''
    feedback = iv
    for i in range(0, len(plaintext), BLOCK_SIZE):
        feedback = encrypt_block(feedback, key)
        cipher_block = xor_bytes(plaintext[i:i+BLOCK_SIZE], feedback)
        ciphertext += cipher_block
    return ciphertext

def decrypt_ofb(ciphertext, key, iv):
    plaintext = b''
    feedback = iv
    for i in range(0, len(ciphertext), BLOCK_SIZE):
        feedback = encrypt_block(feedback, key)
        plain_block = xor_bytes(ciphertext[i:i+BLOCK_SIZE], feedback)
        plaintext += plain_block
    return unpad(plaintext)




if __name__ == "__main__":
    key = 5  # Simple shift key
    iv = b'\x01\x02\x03\x04'  # 4-byte IV
    message = b"Hello Block Modes!"

    print("Original:", message)

    print("\n--- ECB ---")
    e = encrypt_ecb(message, key)
    d = decrypt_ecb(e, key)
    print("Encrypted:", e)
    print("Decrypted:", d)

    print("\n--- CBC ---")
    e = encrypt_cbc(message, key, iv)
    d = decrypt_cbc(e, key, iv)
    print("Encrypted:", e)
    print("Decrypted:", d)

    print("\n--- CFB ---")
    e = encrypt_cfb(message, key, iv)
    d = decrypt_cfb(e, key, iv)
    print("Encrypted:", e)
    print("Decrypted:", d)

    print("\n--- OFB ---")
    e = encrypt_ofb(message, key, iv)
    d = decrypt_ofb(e, key, iv)
    print("Encrypted:", e)
    print("Decrypted:", d)
