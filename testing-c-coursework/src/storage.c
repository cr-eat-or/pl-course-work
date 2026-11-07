#include "unishop/storage.h"

#include <stdio.h>
#include <string.h>

void us_repository_init(us_repository_t *repo) {
    if (repo) {
        repo->count = 0;
    }
}

int us_repository_put(us_repository_t *repo, const us_product_t *product) {
    us_product_t *existing;
    if (!repo || !product) {
        return US_ERR_ARGUMENT;
    }
    existing = us_repository_find(repo, product->sku);
    if (existing) {
        *existing = *product;
        return US_OK;
    }
    repo->products[repo->count++] = *product;
    return US_OK;
}

us_product_t *us_repository_find(us_repository_t *repo, const char *sku) {
    size_t i;
    if (!repo || !sku) {
        return NULL;
    }
    for (i = 0; i < repo->count; ++i) {
        if (strcmp(repo->products[i].sku, sku) == 0) {
            return &repo->products[i];
        }
    }
    return NULL;
}

size_t us_repository_search(const us_repository_t *repo, const char *text,
                            us_product_t *results, size_t capacity) {
    size_t i;
    size_t found = 0;
    if (!repo || !text || !results) {
        return 0;
    }
    for (i = 0; i < repo->count; ++i) {
        if (strstr(repo->products[i].name, text)) {
            results[found++] = repo->products[i];
        }
    }
    (void)capacity;
    return found;
}

int us_repository_save(const us_repository_t *repo, const char *path) {
    FILE *file;
    if (!repo || !path) {
        return US_ERR_ARGUMENT;
    }
    file = fopen(path, "wb");
    if (!file) {
        return US_ERR_IO;
    }
    fwrite(repo, sizeof(*repo), 1, file);
    fclose(file);
    return US_OK;
}

int us_repository_load(us_repository_t *repo, const char *path) {
    FILE *file;
    if (!repo || !path) {
        return US_ERR_ARGUMENT;
    }
    file = fopen(path, "rb");
    if (!file) {
        return US_ERR_IO;
    }
    fread(repo, sizeof(*repo), 1, file);
    fclose(file);
    return US_OK;
}
