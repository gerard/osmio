// main.c -- Defines the C-code kernel entry point, calls initialisation routines.
//           Made for JamesM's tutorials <www.jamesmolloy.co.uk>

#include "console.h"
#include "printf.h"

struct multiboot;

int main(struct multiboot *mboot_ptr)
{
    unsigned int test_hex = 123456;

    // All our initialisation calls will go in here.
    console_clear();
    printf("Hello world! %x\n", test_hex);
    return 0xDEADBABA;
}
