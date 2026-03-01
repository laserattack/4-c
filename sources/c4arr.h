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
        C4ArrHeader *h_;                                                          \
        if (!(arr)) {                                                             \
            h_ = malloc(sizeof(C4ArrHeader) + C4_ARR_INIT_CAP * sizeof(*(arr)));  \
            if (!h_) {                                                            \
                fprintf(stderr, "c4arr alloc err\n");                             \
                exit(1);                                                          \
            }                                                                     \
            h_->cap = C4_ARR_INIT_CAP;                                            \
            h_->len = 0;                                                          \
            (arr) = (void *)h_ + sizeof(C4ArrHeader);                             \
        }                                                                         \
        h_ = c4arrheader(arr);                                                    \
        h_->len++;                                                                \
        if (h_->len > h_->cap) {                                                  \
            h_->cap *= 2;                                                         \
            h_ = realloc(h_, sizeof(C4ArrHeader) + h_->cap * sizeof(*(arr)));     \
            if (!h_) {                                                            \
                fprintf(stderr, "c4arr realloc err\n");                           \
                exit(1);                                                          \
            }                                                                     \
            (arr) = (void *)h_ + sizeof(C4ArrHeader);                             \
        }                                                                         \
        (arr)[h_->len-1] = el;                                                    \
    } while(0)

#define c4arrinsert(arr, idx, el)                                                 \
    do {                                                                          \
        if (!(arr)) break;                                                        \
        if ((idx) <= c4arrlen(arr) && (idx) >= 0) {                               \
            c4arrpush(arr, el);                                                   \
            for (int i_ = c4arrlen(arr) - 1; i_ > (idx); i_--)                    \
                (arr)[i_] = (arr)[i_ - 1];                                        \
            (arr)[idx] = el;                                                      \
        }                                                                         \
    } while(0)

#define c4arrremove(arr, idx)                                                     \
    do {                                                                          \
        if (!(arr)) break;                                                        \
        if ((idx) < c4arrlen(arr) && (idx) >= 0) {                                \
            for (int i_ = (idx); i_ < c4arrlen(arr) - 1; i_++)                    \
                (arr)[i_] = (arr)[i_ + 1];                                        \
            c4arrheader(arr)->len--;                                              \
        }                                                                         \
    } while(0)

#define c4arrshrink(arr)                                                          \
    do {                                                                          \
        if (!(arr)) break;                                                        \
        C4ArrHeader *h_;                                                          \
        h_ = c4arrheader(arr);                                                    \
        h_->cap = h_->len;                                                        \
        if (!h_->cap) {                                                           \
            c4arrfree(arr);                                                       \
        } else {                                                                  \
            h_ = realloc(h_, sizeof(C4ArrHeader) + h_->cap * sizeof(*(arr)));     \
            if (!h_) {                                                            \
                fprintf(stderr, "c4arr realloc err\n");                           \
                exit(1);                                                          \
            }                                                                     \
            (arr) = (void *)h_ + sizeof(C4ArrHeader);                             \
        }                                                                         \
    } while(0)

#endif
