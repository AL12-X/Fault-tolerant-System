#include <stdio.h>

#include "../src/common.hpp"
#include "../src/triple_execution.hpp"

void xy2(int* res, int* x, int* y) {
    *res = (*x + *y) * 2;
}

int main() {
    FT::ErrorStatus err;

    int x = 7;
    int y = 12;

    int res1 = FT::execSubsequent(xy2, &err, &x, &y);
    printf("Subsequent: %d (error: %d)\n", res1, err);

    int res2 = FT::execParallel(xy2, &err, &x, &y);
    printf("Parallel:   %d (error: %d)\n", res2, err);

    return 0;
}