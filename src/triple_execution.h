#include <stdlib.h>
#include <pthread.h>

typedef enum {
    noError,
    withError,
    criticalError
} ErrorStatus;

// Bound to specific number of arguments and their types.
// Only for very complex functions.
int exec_serial(int func(int), int arg, ErrorStatus* err) {
    int res1 = func(arg);
    int res2 = func(arg);
    int res3 = func(arg);

    if (res1 == res2) {
        *err = (res1 == res3) ? noError : withError;
        return res1;
    }

    if (res2 == res3) {
        *err = (res2 == res1) ? noError : withError;
        return res2;
    }

    if (res1 == res3) {
        *err = (res1 == res2) ? noError : withError;
        return res1;
    }

    *err = criticalError;
    return 0;
}

int exec_parallel(void* func(void*), int arg, ErrorStatus* err) {
    int res[] = {arg, arg, arg};

    int rc;
    int i;
    pthread_t threads[3];
    for (i = 0; i < 3; i++) {
        rc = pthread_create(&threads[i], NULL, func, &res[i]); // TODO: add rc check
    }
    for (int i = 0; i < 3; i++){
        pthread_join(threads[i], NULL);
    }

    if (res[0] == res[1]) {
        *err = (res[0] == res[2]) ? noError : withError;
        return res[0];
    }

    if (res[1] == res[2]) {
        *err = (res[1] == res[0]) ? noError : withError;
        return res[1];
    }

    if (res[0] == res[2]) {
        *err = (res[0] == res[1]) ? noError : withError;
        return res[0];
    }

    *err = criticalError;
    return 0;
}

struct ft {
    int (*exec_serial)(int func(int), int arg, ErrorStatus* err);
    int (*exec_parallel)(void* func(void*), int arg, ErrorStatus* err);
} ft = {exec_serial, exec_parallel};
