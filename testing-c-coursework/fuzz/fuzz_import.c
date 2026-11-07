#include <stddef.h>
#include <stdint.h>

#include "unishop/files.h"

int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
    us_product_t product;
    us_parse_product_line(data, size, &product);
    return 0;
}
