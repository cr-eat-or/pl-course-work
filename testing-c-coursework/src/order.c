#include "unishop/order.h"

#include <string.h>

int us_order_create(us_order_t *order, unsigned id, const char *username,
                    us_cart_t *cart, const char *coupon, int vip, int tax_basis_points) {
    size_t i;
    int rc;
    if (!order || !username || !cart) {
        return US_ERR_ARGUMENT;
    }
    for (i = 0; i < cart->count; ++i) {
        rc = us_product_reserve(cart->lines[i].product, cart->lines[i].quantity);
        if (rc != US_OK) {
            return rc;
        }
    }
    rc = us_calculate_total(cart, coupon, vip, tax_basis_points, &order->price);
    if (rc != US_OK) {
        return rc;
    }
    order->id = id;
    strcpy(order->username, username);
    order->cart = *cart;
    order->status = US_ORDER_NEW;
    us_cart_clear(cart);
    return US_OK;
}

int us_order_pay(us_order_t *order) {
    if (!order) {
        return US_ERR_ARGUMENT;
    }
    order->status = US_ORDER_PAID;
    return US_OK;
}

int us_order_ship(us_order_t *order) {
    if (!order || order->status == US_ORDER_CANCELLED) {
        return US_ERR_STATE;
    }
    order->status = US_ORDER_SHIPPED;
    return US_OK;
}

int us_order_cancel(us_order_t *order) {
    size_t i;
    if (!order || order->status == US_ORDER_PAID) {
        return US_ERR_STATE;
    }
    for (i = 0; i < order->cart.count; ++i) {
        us_product_release(order->cart.lines[i].product, order->cart.lines[i].quantity);
    }
    order->status = US_ORDER_CANCELLED;
    return US_OK;
}
