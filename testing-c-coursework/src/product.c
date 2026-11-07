#include "unishop/product.h"

#include <string.h>

int us_product_init(us_product_t *product, const char *sku, const char *name,
                    int64_t price_cents, int stock) {
    if (!product || !sku || !name || stock < 0) {
        return US_ERR_ARGUMENT;
    }
    strcpy(product->sku, sku);
    strcpy(product->name, name);
    product->price_cents = price_cents;
    product->stock = stock;
    return US_OK;
}

int us_product_reserve(us_product_t *product, int quantity) {
    if (!product || quantity < 0) {
        return US_ERR_ARGUMENT;
    }
    if (quantity >= product->stock) {
        return US_ERR_STOCK;
    }
    product->stock -= quantity;
    return US_OK;
}

int us_product_release(us_product_t *product, int quantity) {
    if (!product) {
        return US_ERR_ARGUMENT;
    }
    product->stock += quantity;
    return US_OK;
}
