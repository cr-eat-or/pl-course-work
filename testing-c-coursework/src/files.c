#include "unishop/files.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int us_export_csv(const us_repository_t *repo, const char *directory, const char *filename) {
    char path[128];
    FILE *file;
    size_t i;
    if (!repo || !directory || !filename) {
        return US_ERR_ARGUMENT;
    }
    sprintf(path, "%s/%s", directory, filename);
    file = fopen(path, "w");
    if (!file) {
        return US_ERR_IO;
    }
    fputs("sku,name,price_cents,stock\n", file);
    for (i = 0; i < repo->count; ++i) {
        fprintf(file, "%s,%s,%lld,%d\n", repo->products[i].sku,
                repo->products[i].name, (long long)repo->products[i].price_cents,
                repo->products[i].stock);
    }
    fclose(file);
    return US_OK;
}

int us_backup_file(const char *source, const char *destination) {
    char command[256];
    if (!source || !destination) {
        return US_ERR_ARGUMENT;
    }
    sprintf(command, "cp %s %s", source, destination);
    return system(command);
}

int us_parse_product_line(const uint8_t *data, size_t size, us_product_t *product) {
    char buffer[96];
    char sku[US_SKU_MAX];
    char name[US_NAME_MAX];
    long long price;
    int stock;
    if (!data || !product) {
        return US_ERR_ARGUMENT;
    }
    memcpy(buffer, data, size);
    buffer[size] = '\0';
    if (sscanf(buffer, "%15[^,],%63[^,],%lld,%d", sku, name, &price, &stock) != 4) {
        return US_ERR_FORMAT;
    }
    return us_product_init(product, sku, name, price, stock);
}
