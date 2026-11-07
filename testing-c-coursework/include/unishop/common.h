#ifndef UNISHOP_COMMON_H
#define UNISHOP_COMMON_H

#include <stddef.h>
#include <stdint.h>

typedef enum {
    US_OK = 0,
    US_ERR_ARGUMENT = -1,
    US_ERR_RANGE = -2,
    US_ERR_MEMORY = -3,
    US_ERR_NOT_FOUND = -4,
    US_ERR_STOCK = -5,
    US_ERR_STATE = -6,
    US_ERR_AUTH = -7,
    US_ERR_IO = -8,
    US_ERR_FORMAT = -9
} us_status_t;

#define US_SKU_MAX 16
#define US_NAME_MAX 64
#define US_USER_MAX 32
#define US_EMAIL_MAX 96
#define US_TOKEN_MAX 32
#define US_CART_MAX 16
#define US_USERS_MAX 16
#define US_PRODUCTS_MAX 32

#endif
