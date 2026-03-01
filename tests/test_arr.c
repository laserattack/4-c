#include <stdio.h>

#define C4_ARR_IMPL
#include "../sources/c4arr.h"

int main() {

    int *arr = NULL;

    c4arrpush(arr, 1+2*3);
    c4arrpush(arr, 2);
    c4arrpush(arr, 3);

    for (int i = 0; i < c4arrlen(arr); ++i) {
        printf("el = %i\n", arr[i]);
    }

    c4arrfree(arr);
    
    return 0;
}
