// common.h -- Defines typedefs and some global functions.
// From JamesM's kernel development tutorials.

#ifndef COMMON_H
#define COMMON_H

// Some nice typedefs, to standardise sizes across platforms.
// These typedefs are written for 32-bit X86.
typedef unsigned int   uint32_t;
typedef          int   int32_t;
typedef unsigned short uint16_t;
typedef          short int16_t;
typedef unsigned char  uint8_t;
typedef          char  int8_t;

typedef long (*malloc_f)(uint32_t);

#define assert              (void)
#define NULL                ((void *)0)
#define PANIC(__s)          panic(__FILE__, __LINE__, __s)

void outb(uint16_t port, uint8_t value);
uint8_t inb(uint16_t port);
uint16_t inw(uint16_t port);

void *memset(void *s, int c, uint32_t n);
void sleep(uint32_t jiffies);

void panic(char *file, int line, char *s);

#endif
