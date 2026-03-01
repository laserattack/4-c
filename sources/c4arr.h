#ifndef C4_ARR_H
#define C4_ARR_H

#include <stdio.h>
#include <stdlib.h>

#define C4_ARR_INIT_CAP 1

typedef struct {
    int cap;
    int len;
} C4ArrHeader;

#define c4arrheader(arr) ((arr)? (C4ArrHeader *)((void *)(arr) - sizeof(C4ArrHeader)): NULL)
#define c4arrlen(arr)    ((arr)? (c4arrheader(arr))->len: 0)
#define c4arrcap(arr)    ((arr)? (c4arrheader(arr))->cap: 0)

#define c4arrfree(arr)                                                           \
    do {                                                                         \
        if (!(arr)) break;                                                       \
        free(c4arrheader(arr));                                                  \
        (arr) = NULL;                                                            \
    } while(0)

#define c4arrclear(arr)                                                          \
    do {                                                                         \
        if (!(arr)) break;                                                       \
        (c4arrheader(arr))->len = 0;                                             \
    } while(0)

#define c4arrpush(arr, el)                                                       \
    do {                                                                         \
        C4ArrHeader *h;                                                          \
        if (!(arr)) {                                                            \
            h = malloc(sizeof(C4ArrHeader) + C4_ARR_INIT_CAP * sizeof(*(arr)));  \
            if (!h) {                                                            \
                fprintf(stderr, "c4arr alloc err\n");                            \
                exit(1);                                                         \
            }                                                                    \
            h->cap = C4_ARR_INIT_CAP;                                            \
            h->len = 0;                                                          \
            (arr) = (void *)h + sizeof(C4ArrHeader);                             \
        }                                                                        \
        h = c4arrheader(arr);                                                    \
        h->len++;                                                                \
        if (h->len > h->cap) {                                                   \
            h->cap *= 2;                                                         \
            h = realloc(h, sizeof(C4ArrHeader) + h->cap * sizeof(*(arr)));       \
            if (!h) {                                                            \
                fprintf(stderr, "c4arr realloc err\n");                          \
                exit(1);                                                         \
            }                                                                    \
            (arr) = (void *)h + sizeof(C4ArrHeader);                             \
        }                                                                        \
        (arr)[h->len-1] = el;                                                    \
    } while(0)

#define c4arrinsert(arr, idx, el)                                                \
    do {                                                                         \
        if (!(arr)) break;                                                       \
        if ((idx) <= c4arrlen(arr) && (idx) >= 0) {                              \
            c4arrpush(arr, el);                                                  \
            for (int c4i = c4arrlen(arr) - 1; c4i > (idx); c4i--)                \
                (arr)[c4i] = (arr)[c4i - 1];                                     \
            (arr)[idx] = el;                                                     \
        }                                                                        \
    } while(0)

#define c4arrremove(arr, idx)                                                    \
    do {                                                                         \
        if (!(arr)) break;                                                       \
        if ((idx) < c4arrlen(arr) && (idx) >= 0) {                               \
            for (int c4i = (idx); c4i < c4arrlen(arr) - 1; c4i++)                \
                (arr)[c4i] = (arr)[c4i + 1];                                     \
            c4arrheader(arr)->len--;                                             \
        }                                                                        \
    } while(0)

#define c4arrshrink(arr)                                                         \
    do {                                                                         \
        if (!(arr)) break;                                                       \
        C4ArrHeader *h;                                                          \
        h = c4arrheader(arr);                                                    \
        h->cap = h->len;                                                         \
        h = realloc(h, sizeof(C4ArrHeader) + h->cap * sizeof(*(arr)));           \
        if (!h) {                                                                \
            fprintf(stderr, "c4arr realloc err\n");                              \
            exit(1);                                                             \
        }                                                                        \
        (arr) = (void *)h + sizeof(C4ArrHeader);                                 \
    } while(0)

#endif
