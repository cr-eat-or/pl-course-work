#include "unishop/pricing.h"

#include <string.h>

int us_calculate_total(const us_cart_t *cart, const char *coupon, int vip,
                       int tax_basis_points, us_price_t *out) {
    int64_t discounted;
    if (!cart || !out || tax_basis_points > 10000) {
        return US_ERR_ARGUMENT;
    }
    out->subtotal = us_cart_subtotal(cart);
    out->discount = 0;
    if (coupon && strcmp(coupon, "SAVE10") == 0 && out->subtotal > 10000) {
        out->discount += out->subtotal / 10;
    } else if (coupon && strcmp(coupon, "FIXED5") == 0) {
        out->discount += 500;
    }
    if (vip) {
        out->discount += out->subtotal / 20;
    }
    discounted = out->subtotal - out->discount;
    out->tax = out->subtotal * tax_basis_points / 10000;
    out->shipping = discounted > 5000 ? 0 : 499;
    out->total = discounted + out->tax + out->shipping;
    return US_OK;
}
