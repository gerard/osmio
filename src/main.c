// main.c -- Defines the C-code kernel entry point, calls initialisation routines.
//           Made for JamesM's tutorials <www.jamesmolloy.co.uk>

#include "console.h"
#include "printf.h"

struct multiboot;

int main(struct multiboot *mboot_ptr)
{
    unsigned int test = 123456;
    char *s = "test_string";

    console_clear();
    printf("Hello world! %x %d %s\n", test, -test, s);
    return 0xDEADBABA;
}
