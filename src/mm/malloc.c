#include "common.h"

/* This is defined in linker script */
extern long end;
long placement_address = (long)&end;

static long __kmalloc(uint32_t sz, int align, long *phys)
{
    if (align == 1 && (placement_address & 0xFFFFF000)) {
        // Align it.
        placement_address &= 0xFFFFF000;
        placement_address += 0x1000;
    }

    if (phys) {
        *phys = placement_address;
    }

    long tmp = placement_address;
    placement_address += sz;

    return tmp;
}


long kmalloc(uint32_t sz)   { return __kmalloc(sz, 0, NULL); }
long kmalloc_a(uint32_t sz) { return __kmalloc(sz, 1, NULL); }
long kmalloc_p(uint32_t sz, long *phys)  { return __kmalloc(sz, 0, phys); }
long kmalloc_ap(uint32_t sz, long *phys) { return __kmalloc(sz, 1, phys); }
