#include <iostream>
#include <vector>
#include <stdexcept>
using namespace std;

const int SIZE = 3;
vector<vector<int>> keyMatrix(SIZE, vector<int>(SIZE));

// Forward declarations
void decrypt(string cipherText, string key);

void getKeyMatrix(string key) {
    int k = 0;
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            keyMatrix[i][j] = key[k++] % 65;
        }
    }
}

void encrypt(string message, string key) {
    getKeyMatrix(key);

    while (message.length() % SIZE != 0) {
        message += 'X';  // Padding if message not divisible by SIZE
    }

    string cipherText = "";

    for (size_t i = 0; i < message.length(); i += SIZE) {
        vector<vector<int>> messageVector(SIZE, vector<int>(1));
        vector<vector<int>> cipherMatrix(SIZE, vector<int>(1));

        for (int j = 0; j < SIZE; j++) {
            messageVector[j][0] = message[i + j] % 65;
        }

        for (int r = 0; r < SIZE; r++) {
            cipherMatrix[r][0] = 0;
            for (int c = 0; c < SIZE; c++) {
                cipherMatrix[r][0] += keyMatrix[r][c] * messageVector[c][0];
            }
            cipherMatrix[r][0] %= 26;
            cipherText += (char)(cipherMatrix[r][0] + 65);
        }
    }

    cout << "Ciphertext: " << cipherText << endl;

    // Now call decryption
    decrypt(cipherText, key);
}

int determinant(vector<vector<int>>& mat) {
    int det = mat[0][0]*(mat[1][1]*mat[2][2] - mat[1][2]*mat[2][1])
            - mat[0][1]*(mat[1][0]*mat[2][2] - mat[1][2]*mat[2][0])
            + mat[0][2]*(mat[1][0]*mat[2][1] - mat[1][1]*mat[2][0]);
    return ((det % 26) + 26) % 26;
}

int modInverse(int a, int m) {
    a %= m;
    for (int x = 1; x < m; x++) {
        if ((a * x) % m == 1) return x;
    }
    return -1;
}

int getCofactor(vector<vector<int>>& mat, int p, int q) {
    vector<vector<int>> temp;
    for (int i = 0; i < SIZE; i++) {
        if (i != p) {
            vector<int> row;
            for (int j = 0; j < SIZE; j++) {
                if (j != q) row.push_back(mat[i][j]);
            }
            temp.push_back(row);
        }
    }
    return (temp[0][0]*temp[1][1] - temp[0][1]*temp[1][0] + 26) % 26;
}

vector<vector<int>> adjugateMatrix(vector<vector<int>>& mat) {
    vector<vector<int>> adj(SIZE, vector<int>(SIZE));
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            int sign = ((i + j) % 2 == 0) ? 1 : -1;
            adj[j][i] = (sign * getCofactor(mat, i, j) + 26) % 26;
        }
    }
    return adj;
}

vector<vector<int>> inverseKeyMatrix(vector<vector<int>>& mat) {
    int det = determinant(mat);
    int inv_det = modInverse(det, 26);
    if (inv_det == -1) throw runtime_error("Key matrix is not invertible");

    vector<vector<int>> adj = adjugateMatrix(mat);
    vector<vector<int>> inv(SIZE, vector<int>(SIZE));

    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            inv[i][j] = (adj[i][j] * inv_det) % 26;
        }
    }
    return inv;
}

void decrypt(string cipherText, string key) {
    getKeyMatrix(key);
    vector<vector<int>> invKey = inverseKeyMatrix(keyMatrix);

    if (cipherText.length() % SIZE != 0) {
        throw runtime_error("Invalid ciphertext length.");
    }

    string decryptedText = "";

    for (size_t i = 0; i < cipherText.length(); i += SIZE) {
        vector<vector<int>> cipherVec(SIZE, vector<int>(1));
        vector<vector<int>> decryptedVec(SIZE, vector<int>(1));

        for (int j = 0; j < SIZE; j++) {
            cipherVec[j][0] = cipherText[i + j] % 65;
        }

        for (int r = 0; r < SIZE; r++) {
            decryptedVec[r][0] = 0;
            for (int c = 0; c < SIZE; c++) {
                decryptedVec[r][0] += invKey[r][c] * cipherVec[c][0];
            }
            decryptedVec[r][0] = (decryptedVec[r][0] % 26 + 26) % 26;
            decryptedText += (char)(decryptedVec[r][0] + 65);
        }
    }

    cout << "Decrypted Text: " << decryptedText << endl;
}

int main() {
    string message = "HELA";
    string key = "GYBNQKURP";  // Must be 9 characters

    cout << "Original Message: " << message << endl;
    encrypt(message, key);

    return 0;
}
