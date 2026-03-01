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

#define c4arrfree(arr)                                                            \
    do {                                                                          \
        if (!(arr)) break;                                                        \
        free(c4arrheader(arr));                                                   \
        (arr) = NULL;                                                             \
    } while(0)

#define c4arrclear(arr)                                                           \
    do {                                                                          \
        if (!(arr)) break;                                                        \
        (c4arrheader(arr))->len = 0;                                              \
    } while(0)

#define c4arrpush(arr, el)                                                        \
    do {                                                                          \
        C4ArrHeader *_h;                                                          \
        if (!(arr)) {                                                             \
            _h = malloc(sizeof(C4ArrHeader) + C4_ARR_INIT_CAP * sizeof(*(arr)));  \
            if (!_h) {                                                            \
                fprintf(stderr, "c4arr alloc err\n");                             \
                exit(1);                                                          \
            }                                                                     \
            _h->cap = C4_ARR_INIT_CAP;                                            \
            _h->len = 0;                                                          \
            (arr) = (void *)_h + sizeof(C4ArrHeader);                             \
        }                                                                         \
        _h = c4arrheader(arr);                                                    \
        _h->len++;                                                                \
        if (_h->len > _h->cap) {                                                  \
            _h->cap *= 2;                                                         \
            _h = realloc(_h, sizeof(C4ArrHeader) + _h->cap * sizeof(*(arr)));     \
            if (!_h) {                                                            \
                fprintf(stderr, "c4arr realloc err\n");                           \
                exit(1);                                                          \
            }                                                                     \
            (arr) = (void *)_h + sizeof(C4ArrHeader);                             \
        }                                                                         \
        (arr)[_h->len-1] = el;                                                    \
    } while(0)

#define c4arrinsert(arr, idx, el)                                                 \
    do {                                                                          \
        if (!(arr)) break;                                                        \
        if ((idx) <= c4arrlen(arr) && (idx) >= 0) {                               \
            c4arrpush(arr, el);                                                   \
            for (int _i = c4arrlen(arr) - 1; _i > (idx); _i--)                    \
                (arr)[_i] = (arr)[_i - 1];                                        \
            (arr)[idx] = el;                                                      \
        }                                                                         \
    } while(0)

#define c4arrremove(arr, idx)                                                     \
    do {                                                                          \
        if (!(arr)) break;                                                        \
        if ((idx) < c4arrlen(arr) && (idx) >= 0) {                                \
            for (int _i = (idx); _i < c4arrlen(arr) - 1; _i++)                    \
                (arr)[_i] = (arr)[_i + 1];                                        \
            c4arrheader(arr)->len--;                                              \
        }                                                                         \
    } while(0)

#define c4arrshrink(arr)                                                          \
    do {                                                                          \
        if (!(arr)) break;                                                        \
        C4ArrHeader *_h;                                                          \
        _h = c4arrheader(arr);                                                    \
        _h->cap = _h->len;                                                        \
        if (!_h->cap) {                                                           \
            c4arrfree(arr);                                                       \
        } else {                                                                  \
            _h = realloc(_h, sizeof(C4ArrHeader) + _h->cap * sizeof(*(arr)));     \
            if (!_h) {                                                            \
                fprintf(stderr, "c4arr realloc err\n");                           \
                exit(1);                                                          \
            }                                                                     \
            (arr) = (void *)_h + sizeof(C4ArrHeader);                             \
        }                                                                         \
    } while(0)

#endif
