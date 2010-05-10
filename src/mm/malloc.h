#ifndef MALLOC_H
#define MALLOC_H

long kmalloc(uint32_t sz);
long kmalloc_a(uint32_t sz);
long kmalloc_p(uint32_t sz, long *phys);
long kmalloc_ap(uint32_t sz, long *phys);

#endif
