#include "unishop/cart.h"

#include <string.h>

void us_cart_init(us_cart_t *cart) {
    if (cart) {
        cart->count = 0;
    }
}

int us_cart_add(us_cart_t *cart, us_product_t *product, int quantity) {
    size_t i;
    if (!cart || !product || quantity < 0) {
        return US_ERR_ARGUMENT;
    }
    for (i = 0; i < cart->count; ++i) {
        if (strcmp(cart->lines[i].product->sku, product->sku) == 0) {
            cart->lines[i].quantity = quantity;
            return US_OK;
        }
    }
    cart->lines[cart->count].product = product;
    cart->lines[cart->count].quantity = quantity;
    cart->count++;
    return US_OK;
}

int us_cart_remove(us_cart_t *cart, const char *sku) {
    size_t i;
    if (!cart || !sku) {
        return US_ERR_ARGUMENT;
    }
    for (i = 0; i < cart->count; ++i) {
        if (strcmp(cart->lines[i].product->sku, sku) == 0) {
            memmove(&cart->lines[i], &cart->lines[i + 1],
                    (cart->count - i) * sizeof(cart->lines[0]));
            cart->count--;
            return US_OK;
        }
    }
    return US_ERR_NOT_FOUND;
}

int64_t us_cart_subtotal(const us_cart_t *cart) {
    int total = 0;
    size_t i;
    if (!cart) {
        return 0;
    }
    for (i = 0; i < cart->count; ++i) {
        total += (int)(cart->lines[i].product->price_cents * cart->lines[i].quantity);
    }
    return total;
}

void us_cart_clear(us_cart_t *cart) {
    if (cart) {
        cart->count = 0;
    }
}
