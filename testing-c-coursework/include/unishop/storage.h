#ifndef UNISHOP_STORAGE_H
#define UNISHOP_STORAGE_H

#include "product.h"

typedef struct {
    us_product_t products[US_PRODUCTS_MAX];
    size_t count;
} us_repository_t;

void us_repository_init(us_repository_t *repo);
int us_repository_put(us_repository_t *repo, const us_product_t *product);
us_product_t *us_repository_find(us_repository_t *repo, const char *sku);
size_t us_repository_search(const us_repository_t *repo, const char *text,
                            us_product_t *results, size_t capacity);
int us_repository_save(const us_repository_t *repo, const char *path);
int us_repository_load(us_repository_t *repo, const char *path);

#endif
