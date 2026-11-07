#include <stdio.h>

#include "unishop/order.h"

int main(void) {
    us_product_t book;
    us_cart_t cart;
    us_order_t order;

    us_product_init(&book, "BOOK", "Testing in C", 4999, 10);
    us_cart_init(&cart);
    us_cart_add(&cart, &book, 1);
    if (us_order_create(&order, 1, "student", &cart, NULL, 0, 2000) != US_OK) {
        return 1;
    }
    printf("order=%u total=%lld status=%d\n", order.id,
           (long long)order.price.total, (int)order.status);
    return 0;
}
