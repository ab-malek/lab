vfrom ecdsa import SECP256k1, SigningKey
from Crypto.Cipher import AES
import hashlib
import os

# Generate ECC key pair
sk = SigningKey.generate(curve=SECP256k1)
vk = sk.verifying_key

# Derive shared secret (in real cases, you'd use ECDH)
shared_secret = hashlib.sha256(vk.to_string()).digest()

# Encrypt message
def encrypt_AES(key, plaintext):
    iv = os.urandom(16)
    cipher = AES.new(key, AES.MODE_CFB, iv)
    ciphertext = iv + cipher.encrypt(plaintext.encode())
    return ciphertext

# Decrypt message
def decrypt_AES(key, ciphertext):
    iv = ciphertext[:16]
    cipher = AES.new(key, AES.MODE_CFB, iv)
    plaintext = cipher.decrypt(ciphertext[16:])
    return plaintext.decode()

message = "Hello ECC!"
ciphertext = encrypt_AES(shared_secret, message)
plaintext = decrypt_AES(shared_secret, ciphertext)

print("Original:", message)
print("Decrypted:", plaintext)
