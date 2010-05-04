// main.c -- Defines the C-code kernel entry point, calls initialisation routines.
//           Made for JamesM's tutorials <www.jamesmolloy.co.uk>

#include "console.h"
#include "printf.h"
#include "common.h"
#include "descriptor_tables.h"

struct multiboot;

int main(struct multiboot *mboot_ptr)
{
    unsigned int test = 123456;
    char *s = "test_string";

    init_descriptor_tables();

    console_clear();
    printf("Hello world! %x %d %c %s\n", test, -test, '&', s);
    sleep(1000000);
    printf("Wake up!\n");

    asm volatile ("int $0x3");

    printf("Interrupted\n");
    sleep(1000000);
    printf("and wake up again...\n");

    return 0xDEADBABA;
}
