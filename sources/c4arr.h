#ifndef C4_ARR_H
#define C4_ARR_H

#include <stdio.h>
#include <stdlib.h>

#define C4_ARR_INIT_CAP 1

typedef struct {
    int cap;
    int len;
} C4ArrHeader;

#define c4arrheader(arr) (C4ArrHeader *)((void *)(arr) - sizeof(C4ArrHeader))
#define c4arrlen(arr) (c4arrheader(arr))->len
#define c4arrcap(arr) (c4arrheader(arr))->cap
#define c4arrfree(arr) free(c4arrheader(arr))
#define c4arrpush(arr, el)                                                     \
    do {                                                                       \
        C4ArrHeader *h;                                                        \
        if (!arr) {                                                            \
            h = malloc(sizeof(C4ArrHeader) + C4_ARR_INIT_CAP * sizeof(*arr));  \
            if (!h) {                                                          \
                fprintf(stderr, "c4arr alloc err\n");                          \
                exit(1);                                                       \
            }                                                                  \
            h->cap = C4_ARR_INIT_CAP;                                          \
            h->len = 0;                                                        \
            arr = (void *)h + sizeof(C4ArrHeader);                             \
        }                                                                      \
        h = c4arrheader(arr);                                                  \
        h->len++;                                                              \
        if (h->len == h->cap) {                                                \
            h->cap *= 2;                                                       \
            h = realloc(h, sizeof(C4ArrHeader) + h->cap * sizeof(*arr));       \
            if (!h) {                                                          \
                fprintf(stderr, "c4arr realloc err\n");                        \
                exit(1);                                                       \
            }                                                                  \
            arr = (void *)h + sizeof(C4ArrHeader);                             \
        }                                                                      \
        arr[h->len-1] = el;                                                    \
    } while(0)

#endif
