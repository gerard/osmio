// timer.c -- Initialises the PIT, and handles clock updates.
// Written for JamesM's kernel development tutorials.

#include "timer.h"
#include "isr.h"
#include "printf.h"

static uint32_t ticks;
static uint32_t expiration_tick;
static timer_callback_t expiration_callback;
static void *expiration_arg;

static void timer_callback(registers_t regs)
{
    ticks++;

    if (expiration_tick == ticks) {
        timer_callback_t callback = expiration_callback;
        void *arg = expiration_arg;

        expiration_callback = NULL;
        expiration_arg = NULL;
        expiration_tick = 0;

        callback(arg);
    }
}

void init_timer(uint32_t frequency)
{
   // Firstly, register our timer callback.
   register_interrupt_handler(IRQ0, &timer_callback);

   // The value we send to the PIT is the value to divide it's input clock
   // (1193180 Hz) by, to get our required frequency. Important to note is
   // that the divisor must be small enough to fit into 16-bits.
   uint32_t divisor = 1193180 / frequency;

   // Send the command byte.
   outb(0x43, 0x36);

   // Divisor has to be sent byte-wise, so split here into upper/lower bytes.
   uint8_t l = (uint8_t)(divisor & 0xFF);
   uint8_t h = (uint8_t)( (divisor>>8) & 0xFF );

   // Send the frequency divisor.
   outb(0x40, l);
   outb(0x40, h);

   printf("Timer set up\n");
}

void timer_register(uint32_t when, timer_callback_t what, void *arg)
{
    if (when == 0) {
        what(arg);
    } else {
        expiration_tick = ticks + when;
        expiration_callback = what;
        expiration_arg = arg;
    }
}
