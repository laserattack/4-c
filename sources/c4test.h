#ifndef C4_TEST_H
#define C4_TEST_H

#include <stdio.h>

#define c4runtest(test_fn)                            \
    do {                                              \
        fprintf(stderr, "Running %s... ", #test_fn);  \
        test_fn();                                    \
        fprintf(stderr, "OK\n");                      \
    } while(0)

#endif
