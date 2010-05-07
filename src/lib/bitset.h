#ifndef BITSET_H
#define BITSET_H

#include "common.h"

#define MODULE_NAME "bitset"

typedef uint32_t bitset_field_t;
#define BITSET_BITS_IN_FIELD (sizeof(bitset_field_t) * 8)

/* size should be given in bits */
typedef struct bitset {
    uint32_t size;
    bitset_field_t fields[];
} bitset_t;

bitset_t *bitset_alloc(uint32_t size, malloc_f allocator);

void bitset_set(bitset_t *set, uint32_t addr);
void bitset_clear(bitset_t *set, uint32_t addr);
int bitset_test(bitset_t *set, uint32_t addr);
uint32_t bitset_first_clear(bitset_t *bitset);

#endif
