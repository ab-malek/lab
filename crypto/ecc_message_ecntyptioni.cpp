#include <iostream>
#include <vector>
#include <tuple>
#include <string>
using namespace std;

struct Point {
    long long x, y;
    bool is_infinity;

    Point(long long _x = 0, long long _y = 0, bool inf = false) : x(_x), y(_y), is_infinity(inf) {}

    void print() const {
        if (is_infinity) cout << "Point at Infinity\n";
        else cout << "(" << x << ", " << y << ")\n";
    }
};

// Extended Euclidean Algorithm
long long mod_inv(long long a, long long p) {
    long long t = 0, newt = 1;
    long long r = p, newr = a;

    while (newr != 0) {
        long long quotient = r / newr;
        tie(t, newt) = make_tuple(newt, t - quotient * newt);
        tie(r, newr) = make_tuple(newr, r - quotient * newr);
    }

    if (r > 1) throw runtime_error("No modular inverse");
    if (t < 0) t += p;
    return t;
}

bool is_on_curve(Point P, long long a, long long b, long long p) {
    if (P.is_infinity) return true;
    long long lhs = (P.y * P.y) % p;
    long long rhs = (P.x * P.x * P.x + a * P.x + b) % p;
    return lhs == (rhs + p) % p;
}

Point point_add(Point P, Point Q, long long a, long long p) {
    if (P.is_infinity) return Q;
    if (Q.is_infinity) return P;

    if (P.x == Q.x && (P.y + Q.y) % p == 0)
        return Point(0, 0, true);

    long long m;
    if (P.x == Q.x && P.y == Q.y) {
        long long denom = (2 * P.y) % p;
        if (denom == 0) return Point(0, 0, true);
        m = ((3 * P.x * P.x + a) * mod_inv(denom, p)) % p;
    } else {
        long long denom = (Q.x - P.x + p) % p;
        if (denom == 0) return Point(0, 0, true);
        m = ((Q.y - P.y + p) % p * mod_inv(denom, p)) % p;
    }

    long long x3 = (m * m - P.x - Q.x + 3 * p) % p;
    long long y3 = (m * (P.x - x3) - P.y + 2 * p) % p;
    return Point((x3 + p) % p, (y3 + p) % p);
}

Point scalar_mult(Point P, long long k, long long a, long long p) {
    Point R(0, 0, true);
    while (k > 0) {
        if (k % 2 == 1)
            R = point_add(R, P, a, p);
        P = point_add(P, P, a, p);
        k /= 2;
    }
    return R;
}

string xor_encrypt(string message, long long key) {
    string result = message;
    for (int i = 0; i < message.length(); i++) {
        result[i] = message[i] ^ (key % 256); // Keep within byte range
    }
    return result;
}

int main() {
    // Curve: y^2 = x^3 + ax + b over F_p
    long long a = 1, b = 1, p = 23;
    Point G(3, 10); // Generator

    if (!is_on_curve(G, a, b, p)) {
        cout << "G not on curve\n";
        return 1;
    }

    // Key pairs
    long long na = 6;
    Point Pa = scalar_mult(G, na, a, p);

    long long nb = 15;
    Point Pb = scalar_mult(G, nb, a, p);

    // Shared secret
    Point shared = scalar_mult(Pb, na, a, p);
    long long key = shared.x;

    cout << "Shared ECC Secret: "; shared.print();
    cout << "Derived symmetric key (x): " << key << endl;

    // Message
    string message = "HELLO ECC";
    cout << "\nOriginal: " << message << endl;

    // Encrypt
    string cipher = xor_encrypt(message, key);
    cout << "Encrypted (hex): ";
    for (char c : cipher) printf("%02X ", (unsigned char)c);
    cout << endl;

    // Decrypt
    string decrypted = xor_encrypt(cipher, key);
    cout << "Decrypted: " << decrypted << endl;

    return 0;
}
