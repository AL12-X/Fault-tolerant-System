#include <stdio.h>



int main() {
    int a = 3234;
    int b = 8521;
    const int p = 754;

    int c = a * b;
    int rem_c = c % p;
    int rem_a = a % p;
    int rem_b = b % p;
    int c_mod = rem_a * rem_b;
    int rem_c_mod = c_mod % p;

    if (rem_c == rem_c_mod) {
        printf("Equal");
    } else {
        printf("Not equal");
    }
    printf("\n");

    return 0;
}