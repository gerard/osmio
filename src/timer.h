// timer.h -- Defines the interface for all PIT-related functions.
// Written for JamesM's kernel development tutorials.

#ifndef TIMER_H
#define TIMER_H

#include "common.h"

typedef void (*timer_callback_t)(void *arg);
void init_timer(uint32_t frequency);
void timer_register(uint32_t when, timer_callback_t what, void *arg);


#endif
