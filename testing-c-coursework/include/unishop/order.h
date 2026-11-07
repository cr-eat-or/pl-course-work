#ifndef UNISHOP_ORDER_H
#define UNISHOP_ORDER_H

#include "pricing.h"

typedef enum {
    US_ORDER_NEW,
    US_ORDER_PAID,
    US_ORDER_SHIPPED,
    US_ORDER_CANCELLED
} us_order_status_t;

typedef struct {
    unsigned id;
    char username[US_USER_MAX];
    us_cart_t cart;
    us_price_t price;
    us_order_status_t status;
} us_order_t;

int us_order_create(us_order_t *order, unsigned id, const char *username,
                    us_cart_t *cart, const char *coupon, int vip, int tax_basis_points);
int us_order_pay(us_order_t *order);
int us_order_ship(us_order_t *order);
int us_order_cancel(us_order_t *order);

#endif
