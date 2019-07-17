#include <stdio.h>
#include <math.h>

void rsa() {
    int prime1 = 53;
    int prime2 = 59;

    int k = 2;
    int e = 3;

    long long n = prime1 * prime2;

    long long thetan = (prime1-1)*(prime2-1);

    long long private_key = (k * thetan + 1) / e;

    char msg[] = "Test";
    char encrypted[4];
    char temp;

    for (int i = 0; i < 4; ++i) {
        temp = (msg[i]^e) % n;
        encrypted[i] = temp;
        printf("%d\n", temp);
    }
}