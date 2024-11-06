#include <stdio.h>

typedef struct PUBLIC_KEY {
    int n;
    int e;
} PUBLIC_KEY;

typedef struct SECRET_KEY {
    int d;
    int n;
} SECRET_KEY;

int isCoprime(int a, int b);
int gcd(int a, int b);
int encrypt(int M, int e, int n);
int convertToBinary(int *b, int e);
int decrypt(int encryption_result, int d, int n);
int modular_inverse(int e, int phi);

int main(void) {
    int M;
    PUBLIC_KEY public_key;
    SECRET_KEY secret_key;

    // Type original message
    printf("Please type message: ");
    scanf("%d", &M);

    int p, q;

    // Type two prime numbers
    printf("Please type two prime numbers: ");
    scanf("%d %d", &p, &q);

    // n value of public, secret key
    public_key.n = p * q;
    secret_key.n = p * q;

    int euclid_n = (p - 1) * (q - 1);

    // Find e value of public key
    for (int i = 3; i < euclid_n; i += 2) { // start from 3 for odd numbers
        if (isCoprime(i, euclid_n)) {
            public_key.e = i;
            break;
        }
    }
    
    // find d value of secret key
    int j = 1;
    while(1) {
        if ((euclid_n * j + 1) % public_key.e == 0) {
            secret_key.d = (euclid_n * j + 1) / public_key.e;
            break;
        }
        j++;
    }

    // Encryption
    int encrypt_result;
    encrypt_result = encrypt(M, public_key.e, public_key.n);
    printf("Encryption result is: %d\n", encrypt_result);

    // Decryption
    int decryption_result;
    decryption_result = decrypt(encrypt_result, secret_key.d, secret_key.n);
    printf("Decryption result (original message) is: %d\n", decryption_result);

    return 0;
}

// Check if two numbers are coprime. If coprime, return 1, else return 0
int isCoprime(int a, int b) {
    return gcd(a, b) == 1;
}

// Calculate gcd
int gcd(int a, int b) {
    return b == 0 ? a : gcd(b, a % b);
}

// Function for encryption
// Calculate result of M^e mod n = ??
int encrypt(int M, int e, int n) {
    int b[20];
    int d = 1;

    // Convert e value to binary number and store in array b
    int bit_count = convertToBinary(b, e);

    for (int i = bit_count - 1; i >= 0; i--) {
        d = (d * d) % n;
        if (b[i] == 1) {
            d = (d * M) % n;
        }
    }

    return d;
}

int convertToBinary(int *b, int e) {
    int i = 0;
    while (e > 0) {
        b[i] = e % 2;
        e = e / 2;
        i++;
    }
    // Fill the remaining bits with 0s
    for (; i < 20; i++) {
        b[i] = 0;
    }
    return i; // Return the number of bits used
}

int decrypt(int encryption_result, int d, int n) {
    int b[20];
    int r = 1;

    int bit_count = convertToBinary(b, d);

    for (int i = bit_count - 1; i >= 0; i--) {
        r = (r * r) % n;
        if (b[i] == 1) {
            r = (r * encryption_result) % n;
        }
    }

    return r;
}

