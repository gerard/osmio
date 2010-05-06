#include "common.h"
#include "isr.h"
#include "printf.h"

static void keyboard_callback(registers_t regs)
{
    uint8_t scode = inb(0x60);
    printf("Got scancode: %x", scode);

    /* ACK */
    outb(0x20, 0x20);
}

void init_keyboard()
{
    register_interrupt_handler(IRQ1, &keyboard_callback);
}


