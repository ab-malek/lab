# Block size in bytes
BLOCK_SIZE = 4

# Simple "encryption" function (for demonstration)
def encrypt_block(block, key):
    return bytes([(b + key) % 256 for b in block])

# Simple "decryption" function (reverses the above)
def decrypt_block(block, key):
    return bytes([(b - key) % 256 for b in block])

# Pad with zero bytes (for simplicity)
def pad(data):
    padding_len = BLOCK_SIZE - (len(data) % BLOCK_SIZE)
    return data + bytes([0] * padding_len)

# ECB Encryption
def encrypt_ecb(plaintext, key):
    plaintext = pad(plaintext)
    ciphertext = b''
    for i in range(0, len(plaintext), BLOCK_SIZE):
        block = plaintext[i:i+BLOCK_SIZE]
        encrypted = encrypt_block(block, key)
        ciphertext += encrypted
    return ciphertext

# ECB Decryption
def decrypt_ecb(ciphertext, key):
    plaintext = b''
    for i in range(0, len(ciphertext), BLOCK_SIZE):
        block = ciphertext[i:i+BLOCK_SIZE]
        decrypted = decrypt_block(block, key)
        plaintext += decrypted
    return plaintext.rstrip(b'\x00')  # remove padding

# Example usage
if __name__ == "__main__":
    key = 3  # A small number as a 'key' for demo
    message = b"HELLO ECB MODE DEMO asdf asdf"

    print("Original:", message)

    encrypted = encrypt_ecb(message, key)
    print("Encrypted:", encrypted)

    decrypted = decrypt_ecb(encrypted, key)
    print("Decrypted:", decrypted)
