#ifndef UNISHOP_CART_H
#define UNISHOP_CART_H

#include "product.h"

typedef struct {
    us_product_t *product;
    int quantity;
} us_cart_line_t;

typedef struct {
    us_cart_line_t lines[US_CART_MAX];
    size_t count;
} us_cart_t;

void us_cart_init(us_cart_t *cart);
int us_cart_add(us_cart_t *cart, us_product_t *product, int quantity);
int us_cart_remove(us_cart_t *cart, const char *sku);
int64_t us_cart_subtotal(const us_cart_t *cart);
void us_cart_clear(us_cart_t *cart);

#endif
