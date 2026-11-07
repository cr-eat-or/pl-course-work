#ifndef UNISHOP_PRICING_H
#define UNISHOP_PRICING_H

#include "cart.h"

typedef struct {
    int64_t subtotal;
    int64_t discount;
    int64_t tax;
    int64_t shipping;
    int64_t total;
} us_price_t;

int us_calculate_total(const us_cart_t *cart, const char *coupon, int vip,
                       int tax_basis_points, us_price_t *out);

#endif
