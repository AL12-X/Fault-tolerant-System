// cc demo.c -pthread

#include <stdio.h>

#include "triple_execution.h"

int x2_serial(int x) {
    return x * 2;
}

void* x2_parallel(void* x) {
    int* intPtr = x;
    *intPtr *= 2;
}

int main() {
    ErrorStatus* err = (ErrorStatus*)malloc(sizeof(int));

    int res1 = ft.exec_serial(x2_serial, 42, err);
    int res2 = ft.exec_parallel(x2_parallel, 42, err);

    printf("Serial: %d (error: %d)\n", res1, *err);
    printf("Parallel: %d (error: %d)\n", res2, *err);

    return 0;
}