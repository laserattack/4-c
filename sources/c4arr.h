#ifndef C4_ARR_H
#define C4_ARR_H

#ifdef C4_ARR_IMPL

#include <stdlib.h>

#define C4_ARR_INIT_CAP 1

typedef struct {
    int cap;
    int len;
} C4ArrHeader;

#define c4arrheader(arr) (C4ArrHeader *)((void *)(arr) - sizeof(C4ArrHeader))
#define c4arrlen(arr) (c4arrheader(arr))->len
#define c4arrfree(arr) free(c4arrheader(arr));
#define c4arrpush(arr, el)                                                      \
    do {                                                                        \
        C4ArrHeader *c4h;                                                       \
        if (!arr) {                                                             \
            c4h = malloc(sizeof(C4ArrHeader) + C4_ARR_INIT_CAP * sizeof(*arr)); \
            if (!c4h) {                                                         \
                fprintf(stderr, "c4arr alloc err\n");                           \
                exit(1);                                                        \
            }                                                                   \
            c4h->cap = C4_ARR_INIT_CAP;                                         \
            c4h->len = 0;                                                       \
            arr = (void *)c4h + sizeof(C4ArrHeader);                            \
        }                                                                       \
        c4h = c4arrheader(arr);                                                 \
        c4h->len++;                                                             \
        if (c4h->len == c4h->cap) {                                             \
            c4h->cap *= 2;                                                      \
            c4h = realloc(c4h, sizeof(C4ArrHeader) + c4h->cap * sizeof(*arr));  \
            if (!c4h) {                                                         \
                fprintf(stderr, "c4arr realloc err\n");                         \
                exit(1);                                                        \
            }                                                                   \
            arr = (void *)c4h + sizeof(C4ArrHeader);                            \
        }                                                                       \
        arr[c4h->len-1] = el;                                                   \
    } while(0)

#endif

#endif
