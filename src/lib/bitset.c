#include "bitset.h"

static int INDEX(uint32_t addr) { return addr / BITSET_BITS_IN_FIELD; }
static int OFFSET(uint32_t addr) { return addr % BITSET_BITS_IN_FIELD; }

bitset_t *bitset_alloc(uint32_t size, malloc_f allocator)
{
    uint32_t bitset_size;
    bitset_t *new;

    /* Misuse just returns NULL.  Here, size is not aligned */
    if (OFFSET(size)) {
        return NULL;
    }

    bitset_size = sizeof(bitset_t);
    bitset_size += INDEX(size) * sizeof(bitset_field_t);

    new = (bitset_t *)allocator(bitset_size);
    memset(new, 0, bitset_size);
    new->size = size;

    return new;
}

void bitset_set(bitset_t *bitset, uint32_t addr)
{
    bitset->fields[INDEX(addr)] |= (0x1 << OFFSET(addr));
}

void bitset_clear(bitset_t *bitset, uint32_t addr)
{
    bitset->fields[INDEX(addr)] &= ~(0x1 << OFFSET(addr));
}

int bitset_test(bitset_t *bitset, uint32_t addr)
{
    return !!(bitset->fields[INDEX(addr)] & (0x1 << OFFSET(addr)));
}

uint32_t bitset_first_clear(bitset_t *bitset)
{
    for (int i = 0; i < INDEX(bitset->size); i++) {
        if (bitset->fields[i] == ((bitset_field_t)-1)) continue;

        for (int j = 0; j < BITSET_BITS_IN_FIELD; j++) {
            if ((bitset->fields[i] & (0x1 << j))) continue;
            return i * BITSET_BITS_IN_FIELD + j;
        }
    }

    return (uint32_t)0xFFFFFFFF;
}
