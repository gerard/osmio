// main.c -- Defines the C-code kernel entry point, calls initialisation routines.
//           Made for JamesM's tutorials <www.jamesmolloy.co.uk>

#include "console.h"
#include "printf.h"
#include "common.h"
#include "descriptor_tables.h"
#include "timer.h"
#include "keyboard.h"

struct multiboot;

void enable_interrupts()
{
    asm volatile ("sti");
}

void sleep_callback(void *arg)
{
    printf("Clock ticking: %d\n", (int)arg);
    timer_register(100, sleep_callback, (void *)((int)arg + 1));
}

int main(struct multiboot *mboot_ptr)
{
    init_descriptor_tables();
    init_keyboard();
    init_timer(100);

    /* Register a timer to trigger in 100 ticks (1 sec) */
    timer_register(100, sleep_callback, (void *)0);

    enable_interrupts();
    console_clear();

    /* Now wait for the timer to trigger ... */
    return 0;
}
