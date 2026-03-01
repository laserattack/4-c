#include <stdio.h>
#include <assert.h>
#include <string.h>

#include "../sources/c4arr.h"
#include "../sources/c4test.h"
#include "../sources/c4arg.h"

// ================ TEST ARG PARSER ================

void test_arg() {
    int argc = 4;
    char **argv = (char *[]){"./program", "-a", "-b", "-c", NULL};
    char *c4argv0;

    int res = 0;
    c4argbegin {
        case 'c':
            res += 2;
            break;
        case 'b':
            res += 3;
            break;
        case 'a':
            res += 5;
            break;
    } c4argend;

    assert(res == 10);
    assert(argc == 0);
    assert(!strcmp(c4argv0, "./program"));
}

// ================ TEST ARG PARSER ================


// ================ TEST DYNARR ================

void test_arr_diff_types() {
    int   *arri    = NULL;
    float *arrf    = NULL;
    char  **arrstr = NULL;
    struct point { int x; int y; } *arrpt = NULL;

    c4arrpush(arri, 5);
    c4arrpush(arrf, 9.2f);
    c4arrpush(arrstr, "hello, sailor!");
    c4arrpush(arrpt, ((struct point){1, 2}));

    assert(arri[0] == 5);
    assert(arrf[0] == 9.2f);
    assert(!strcmp(arrstr[0], "hello, sailor!"));
    assert(arrpt[0].x == 1);

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

// ================ TEST DYNARR ================

int main() {
    c4runtest(test_arr_push);
    c4runtest(test_arr_diff_types);
    c4runtest(test_arg);
    return 0;
}
