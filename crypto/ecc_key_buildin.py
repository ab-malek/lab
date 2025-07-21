from cryptography.hazmat.primitives.asymmetric import ec
from cryptography.hazmat.primitives import serialization

# Alice generates her private key
alice_private_key = ec.generate_private_key(ec.SECP256R1())
alice_public_key = alice_private_key.public_key()

# Bob generates his private key
bob_private_key = ec.generate_private_key(ec.SECP256R1())
bob_public_key = bob_private_key.public_key()

# Alice and Bob exchange public keys
# Both parties compute the shared secret
alice_shared_secret = alice_private_key.exchange(ec.ECDH(), bob_public_key)
bob_shared_secret = bob_private_key.exchange(ec.ECDH(), alice_public_key)

print("Shared secret is equal:", alice_shared_secret == bob_shared_secret)
