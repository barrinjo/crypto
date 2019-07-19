#include <stdio.h>
#include <math.h>
#include <string.h>

#define MAX_LENGTH 256

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

void rsaEncrypt(char msg[], double prime_1, double prime_2, int k) {

    double n = prime_1 * prime_2;

    double phi = (prime_1-1)*(prime_2-1);
    int e = 2;

    while (e < phi) {
        if (gcd(e, phi) == 1)
            break;
        else
            ++e;
    }

    long long private_key = ((k * phi) + 1) / e;

    printf("%lld\n", private_key);

    char temp;
    char encrypted_msg[MAX_LENGTH];
    char decrypted_msg[MAX_LENGTH];

    for (int i = 0; i < strlen(msg); ++i) {
        temp = fmod(pow(msg[i], e), n);
        encrypted_msg[i] = temp;
        printf("%c\n", encrypted_msg[i]);
    }

    for (int i = 0; i < strlen(msg); ++i) {
        decrypted_msg[i] = fmod(pow(encrypted_msg[i], private_key), n);
        printf("%c\n", decrypted_msg[i]);
    }

}

int main (int argc, char *argv[]) {
    char msg[] = "test";
    double prime_1 = 13;
    double prime_2 = 17;
    int k = 2;

    rsaEncrypt(msg, prime_1, prime_2, k);
    return 0;
}