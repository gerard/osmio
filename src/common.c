// common.c -- Defines some global functions.
// From JamesM's kernel development tutorials.

#include "common.h"

// Write a byte out to the specified port.
void outb(uint16_t port, uint8_t value)
{
    asm volatile ("outb %1, %0" : : "dN" (port), "a" (value));
}

uint8_t inb(uint16_t port)
{
   uint8_t ret;
   asm volatile("inb %1, %0" : "=a" (ret) : "dN" (port));
   return ret;
}

uint16_t inw(uint16_t port)
{
   uint16_t ret;
   asm volatile ("inw %1, %0" : "=a" (ret) : "dN" (port));
   return ret;
}

void *memset(void *s, int c, uint32_t n)
{
    for(int i = 0; i < n; i++) ((uint8_t *)s)[i] = c & 0xFF;
    return s;
}

void sleep(uint32_t jiffies)
{
    while(jiffies--) {
        asm volatile("pause");
        asm volatile("pause");
        asm volatile("pause");
        asm volatile("pause");
        asm volatile("pause");
    }
}
