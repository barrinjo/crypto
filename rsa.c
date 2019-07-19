#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <math.h>

int EXPONENT, PRIVATE_KEY, PUBLIC_KEY;

int gcd(int a, int h) {
    int temp;
    while(1) {
        temp = a % h;
        if (temp == 0) {
            return h;
        }
        a = h;
        h = temp;
    }
}

int inverse(int in1, int in2) {
    int inverse;
    int in1_temp = in1;
    int quotient, remainder;

    int t;

    int temp1 = 0;
    int temp2 = 1;

    while (in2 > 0) {
        quotient = in1 / in2;
        remainder = in1 - (quotient * in2);
        in1 = in2;
        in2 = remainder;

        t = temp1 - (quotient * temp2);
        temp1 = temp2;
        temp2 = t;
    }

    if (in1 == 1) {
        inverse = temp1;
    }

    if (inverse < 0) {
        inverse = inverse + in1_temp;
    }

    return inverse;
}

void fastExponent(int bit, int n, int* y, int* a) {
    if (bit == 1)
        *y = (*y * (*a)) % n;
    
    *a = (*a) * (*a) % n;
}

int find(int a, int m, int n) {
    int r;
    int y = 1;

    while (m > 0) {
        r = m % 2;
        fastExponent(r, n, &y, &a);
        m = m / 2;
    }
    return y;
}

void encrypt(int char_value, FILE* out_stream) {
    int cipher;
    cipher = find(char_value, EXPONENT, PUBLIC_KEY);
    fprintf(out_stream, "%d ", cipher);
}

void decrypt(int char_value, FILE* out_stream) {
    int decipher;
    decipher = find(char_value, PRIVATE_KEY, PUBLIC_KEY);
    fprintf(out_stream, "%c", decipher);
}

void keyGen(int prime1, int prime2) {
    int phi;

    PUBLIC_KEY = prime1 * prime2;

    phi = (prime1 - 1) * (prime2 - 1);

    EXPONENT = rand() % (phi - 2) + 2;

    while (gcd(phi, EXPONENT) != 1) {
        EXPONENT = rand() % (phi - 2) + 2;
    }

    PRIVATE_KEY = inverse(phi, EXPONENT);
}

int main (int argc, char *argv[]) {
    /* Check for input file name */
    if (argc < 2) {
        printf("Error: Provide file name\n");
        exit(1);
    }

    FILE *in_stream, *out_stream;

    /* Destroy previous runs */
    out_stream = fopen("encrypted.txt", "w+");
    fclose(out_stream);
    out_stream = fopen("decrypted.txt", "w+");
    fclose(out_stream);

    in_stream = fopen(argv[1], "r+");

    /* Check for file open error */
    if (in_stream == NULL) {
        printf("Error: Could not open source file\n");
        exit(1);
    }

    out_stream = fopen("encrypted.txt", "w+");

    /* Check for file open error */
    if (out_stream == NULL) {
        printf("Error: Could not open output file\n");
        exit(1);
    }

    int prime1, prime2;

    /* These are developement values. Make sure they are small...

    TODO:
    change data types from int to larger value to allow for larger primes 
    REPLACE BEFORE MERGE WITH MASTER */
    prime1 = 73;
    prime2 = 41;

    keyGen(prime1, prime2);

    /* Encrypt */
    while (1) {
        char current_char = getc(in_stream);
        if (current_char == -1)
            break;
        int char_value = toascii(current_char);
        encrypt(char_value, out_stream);
    }

    fclose(in_stream);
    fclose(out_stream);

    /* Decrypt */
    in_stream = fopen("encrypted.txt", "r+");
    if (in_stream == NULL) {
        printf("Error: Could not open encrypted file\n");
        exit(1);
    }

    out_stream = fopen("decrypted.txt", "w+");
    if (out_stream == NULL) {
        printf("Error: Could not open decrypted file\n");
        exit(1);
    }

    while (1) {
        int decryption_input;
        if (fscanf(in_stream, "%d", &decryption_input) == -1)
            break;
        decrypt(decryption_input, out_stream);
    }

    fclose(in_stream);
    fclose(out_stream);
    
    return 0;
}