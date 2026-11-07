#ifndef MINITEST_H
#define MINITEST_H

#include <stdio.h>
#include <string.h>

static int mt_failures = 0;
static int mt_tests = 0;

#define MT_ASSERT_TRUE(expr) do { \
    if (!(expr)) { \
        fprintf(stderr, "%s:%d: assertion failed: %s\n", __FILE__, __LINE__, #expr); \
        mt_failures++; \
        return; \
    } \
} while (0)

#define MT_ASSERT_INT_EQ(expected, actual) \
    MT_ASSERT_TRUE((long long)(expected) == (long long)(actual))

#define MT_ASSERT_STR_EQ(expected, actual) \
    MT_ASSERT_TRUE(strcmp((expected), (actual)) == 0)

#define MT_RUN(test_fn) do { \
    int before = mt_failures; \
    mt_tests++; \
    test_fn(); \
    printf("[%s] %s\n", before == mt_failures ? "PASS" : "FAIL", #test_fn); \
} while (0)

#define MT_RESULT() (printf("%d tests, %d failures\n", mt_tests, mt_failures), \
                     mt_failures == 0 ? 0 : 1)

#endif
