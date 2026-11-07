#ifndef UNISHOP_FILES_H
#define UNISHOP_FILES_H

#include "storage.h"

int us_export_csv(const us_repository_t *repo, const char *directory, const char *filename);
int us_backup_file(const char *source, const char *destination);
int us_parse_product_line(const uint8_t *data, size_t size, us_product_t *product);

#endif
