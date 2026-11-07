#include "minitest.h"

#include "unishop/order.h"
#include "unishop/storage.h"

static void test_product_regular_initialization(void) {
    us_product_t product;
    MT_ASSERT_INT_EQ(US_OK, us_product_init(&product, "A-1", "Keyboard", 2000, 5));
    MT_ASSERT_STR_EQ("A-1", product.sku);
    MT_ASSERT_INT_EQ(2000, product.price_cents);
}

static void test_regular_cart_subtotal(void) {
    us_product_t a;
    us_product_t b;
    us_cart_t cart;
    us_product_init(&a, "A", "A", 1000, 5);
    us_product_init(&b, "B", "B", 500, 5);
    us_cart_init(&cart);
    us_cart_add(&cart, &a, 2);
    us_cart_add(&cart, &b, 1);
    MT_ASSERT_INT_EQ(2500, us_cart_subtotal(&cart));
}

static void test_regular_total(void) {
    us_product_t product;
    us_cart_t cart;
    us_price_t price;
    us_product_init(&product, "A", "A", 1000, 5);
    us_cart_init(&cart);
    us_cart_add(&cart, &product, 1);
    MT_ASSERT_INT_EQ(US_OK, us_calculate_total(&cart, NULL, 0, 2000, &price));
    MT_ASSERT_INT_EQ(1699, price.total);
}

int main(void) {
    MT_RUN(test_product_regular_initialization);
    MT_RUN(test_regular_cart_subtotal);
    MT_RUN(test_regular_total);
    return MT_RESULT();
}
