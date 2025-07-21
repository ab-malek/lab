# Elliptic Curve Parameters (a small prime for simplicity)
a = 2
b = 3
p = 97  # prime number (modulus)
G = (3, 6)  # base point on the curve

# Extended Euclidean Algorithm to find modular inverse
def modinv(a, p):
    if a == 0:
        raise ValueError("No inverse exists")
    lm, hm = 1, 0
    low, high = a % p, p
    while low > 1:
        ratio = high // low
        nm = hm - lm * ratio
        new = high - low * ratio
        lm, low, hm, high = nm, new, lm, low
    return lm % p

# Point Addition
def ecc_add(p1, p2):
    if p1 == (None, None):
        return p2
    if p2 == (None, None):
        return p1

    x1, y1 = p1
    x2, y2 = p2

    if x1 == x2 and y1 != y2:
        return (None, None)

    if p1 == p2:
        # Point doubling
        m = (3 * x1 * x1 + a) * modinv(2 * y1, p) % p
    else:
        # Point addition
        m = (y2 - y1) * modinv(x2 - x1, p) % p

    x3 = (m * m - x1 - x2) % p
    y3 = (m * (x1 - x3) - y1) % p

    return (x3, y3)

# Scalar Multiplication (repeated point addition)
def scalar_mult(k, point):
    result = (None, None)  # point at infinity
    for i in range(k):
        result = ecc_add(result, point)
    return result

# Generate private/public keys
def generate_keypair():
    private_key = 7  # Example static private key (can be random)
    public_key = scalar_mult(private_key, G)
    return private_key, public_key

# Simulate ECDH Key Exchange
def ecdh_key_exchange():
    print("== Key Exchange Using ECC ==")
    # Alice
    alice_private, alice_public = generate_keypair()
    print("Alice's Public Key:", alice_public)

    # Bob
    bob_private, bob_public = generate_keypair()
    print("Bob's Public Key:", bob_public)

    # Shared secret
    alice_shared = scalar_mult(alice_private, bob_public)
    bob_shared = scalar_mult(bob_private, alice_public)

    print("Alice's Shared Secret:", alice_shared)
    print("Bob's Shared Secret:  ", bob_shared)
    print("Shared Secret Match? ", alice_shared == bob_shared)

# Run key exchange
ecdh_key_exchange()
