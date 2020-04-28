#include <stdio.h>

#include "../src/common.hpp"
#include "../src/two_core_redundancy.hpp"

void func(long long* res, int* x) {
    volatile long long i;
    for (i = 0; i < 1e9; ++i) {}
    *res = i + *x;
}

int main() {
    FT::ErrorStatus err;

    int x = 42;

    long long res = FT::runOn2Cores(func, &err, &x);
    printf("Result: %lld (error: %d)\n", res, err);

    return 0;
}