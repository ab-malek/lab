#include <iostream>
#include <vector>
#include <cmath>
using namespace std;

// GCD
int gcd(int a, int b) {
    if (b == 0)
        return a;
    return gcd(b, a % b);
}

// Extended Euclidean Algorithm for modular inverse
int modInverse(int e, int phi) {
    int t = 0, newt = 1;
    int r = phi, newr = e;
    while (newr != 0) {
        int quotient = r / newr;
        int temp = newt;
        newt = t - quotient * newt;
        t = temp;

        temp = newr;
        newr = r - quotient * newr;
        r = temp;
    }
    if (r > 1) return -1;
    if (t < 0) t += phi;
    return t;
}

// Modular exponentiation
long long modExp(long long base, long long exp, long long mod) {
    long long result = 1;
    base %= mod;
    while (exp > 0) {
        if (exp % 2 == 1)
            result = (result * base) % mod;
        base = (base * base) % mod;
        exp /= 2;
    }
    return result;
}

int main() {
    // Step 1: Choose primes
    int p = 61, q = 53;
    int n = p * q;
    int phi = (p - 1) * (q - 1);
    int e = 17;

    // Step 2: Calculate private key d
    int d = modInverse(e, phi);
    if (d == -1) {
        cout << "Modular inverse not found." << endl;
        return 0;
    }

    cout << "Public Key: (" << e << ", " << n << ")\n";
    cout << "Private Key: (" << d << ", " << n << ")\n";

    // Step 3: Take string input
    string message;
    cout << "Enter a message to encrypt: ";
    getline(cin, message);

    // Step 4: Encrypt each character
    vector<long long> encryptedMessage;
    for (char ch : message) {
        int asciiVal = (int)ch;
        long long cipher = modExp(asciiVal, e, n);
        encryptedMessage.push_back(cipher);
    }

    cout << "\nEncrypted message (as numbers): ";
    for (long long val : encryptedMessage)
        cout << val << " ";
    cout << endl;

    // Step 5: Decrypt
    string decryptedMessage = "";
    for (long long cipher : encryptedMessage) {
        char decryptedChar = (char)modExp(cipher, d, n);
        decryptedMessage += decryptedChar;
    }

    cout << "\nDecrypted message: " << decryptedMessage << endl;

    return 0;
}
