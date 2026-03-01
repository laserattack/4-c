#include <stdio.h>
#include <assert.h>

#include "../sources/c4arr.h"
#include "../sources/c4test.h"

void test_arr_diff_types() {
    int   *arri    = NULL;
    float *arrf    = NULL;
    char  **arrstr = NULL;
    struct point { int x; int y; } *arrpt = NULL;

    c4arrpush(arri, 5);
    c4arrpush(arrf, 9.2);
    c4arrpush(arrstr, "hello, sailor!");
    (struct point){1, 2};

    c4arrfree(arri);
    c4arrfree(arrf);
    c4arrfree(arrstr);
    c4arrfree(arrpt);
}

void test_arr_push() {
    int *arr = NULL;

    c4arrpush(arr, 1+2*3);
    c4arrpush(arr, 2);
    c4arrpush(arr, 3);

    assert(c4arrlen(arr) == 3 && "incorrect arr len");
    assert(c4arrcap(arr) == 4 && "incorrect arr cap");

    c4arrfree(arr);
}

int main() {
    c4runtest(test_arr_push);
    c4runtest(test_arr_diff_types);
    return 0;
}
