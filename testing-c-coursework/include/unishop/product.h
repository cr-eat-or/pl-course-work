#ifndef UNISHOP_PRODUCT_H
#define UNISHOP_PRODUCT_H

#include "common.h"

typedef struct {
    char sku[US_SKU_MAX];
    char name[US_NAME_MAX];
    int64_t price_cents;
    int stock;
} us_product_t;

int us_product_init(us_product_t *product, const char *sku, const char *name,
                    int64_t price_cents, int stock);
int us_product_reserve(us_product_t *product, int quantity);
int us_product_release(us_product_t *product, int quantity);

#endif
