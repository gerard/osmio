#include "common.h"
#include "isr.h"
#include "printf.h"

static const char scode_to_char_tbl[256] = {
    [0x1e] = 'a',
    [0x1f] = 's',
    [0x20] = 'd',
    [0x21] = 'f',
    [0x22] = 'g',
    [0x23] = 'h',
    [0x24] = 'j',
};

static inline uint8_t scode_is_break(uint8_t c) { return c & 0x80; }

static void keyboard_callback(registers_t regs)
{
    uint8_t scode = inb(0x60);

    /* FIXME: Design thingie...
     * Try to move this to a workqueue or something like that.  It doesn't seem
     * right to do this in interrupt context.
     */
    if (!scode_is_break(scode)) {
        char c = scode_to_char_tbl[scode];
        if (c) printf("%c", c);
        else printf("Unknown scancode: %x\n", scode);
    }

    /* ACK */
    outb(0x20, 0x20);
}

void init_keyboard()
{
    register_interrupt_handler(IRQ1, &keyboard_callback);
}


