//
// descriptor_tables.c - Initialises the GDT and IDT, and defines the 
// default ISR and IRQ handler.
// Based on code from Bran's kernel development tutorials.
// Rewritten for JamesM's kernel development tutorials.
//

#include "common.h"
#include "descriptor_tables.h"

// Lets us access our ASM functions from our C code.
extern void gdt_flush(uint32_t);
extern void idt_flush(uint32_t);

// Internal function prototypes.
static void init_gdt();
static void gdt_set_gate(int32_t, uint32_t, uint32_t, uint8_t, uint8_t);
static void init_idt();
static void idt_set_gate(uint8_t, uint32_t, uint16_t, uint8_t);

gdt_entry_t gdt_entries[5];
gdt_ptr_t   gdt_ptr;
idt_entry_t idt_entries[256];
idt_ptr_t   idt_ptr;

// Initialisation routine - zeroes all the interrupt service routines,
// initialises the GDT and IDT.
void init_descriptor_tables()
{
   init_gdt();
   init_idt();
}

static void init_gdt()
{
   gdt_ptr.limit = (sizeof(gdt_entry_t) * 5) - 1;
   gdt_ptr.base  = (uint32_t)&gdt_entries;

   gdt_set_gate(0, 0, 0, 0, 0);                // Null segment
   gdt_set_gate(1, 0, 0xFFFFFFFF, 0x9A, 0xCF); // Code segment
   gdt_set_gate(2, 0, 0xFFFFFFFF, 0x92, 0xCF); // Data segment
   gdt_set_gate(3, 0, 0xFFFFFFFF, 0xFA, 0xCF); // User mode code segment
   gdt_set_gate(4, 0, 0xFFFFFFFF, 0xF2, 0xCF); // User mode data segment

   gdt_flush((uint32_t)&gdt_ptr);
}

// Set the value of one GDT entry.
static void gdt_set_gate(int32_t num, uint32_t base, uint32_t limit, uint8_t access, uint8_t gran)
{
   gdt_entries[num].base_low    = (base & 0xFFFF);
   gdt_entries[num].base_middle = (base >> 16) & 0xFF;
   gdt_entries[num].base_high   = (base >> 24) & 0xFF;

   gdt_entries[num].limit_low   = (limit & 0xFFFF);
   gdt_entries[num].granularity = (limit >> 16) & 0x0F;

   gdt_entries[num].granularity |= gran & 0xF0;
   gdt_entries[num].access      = access;
}

static void init_idt()
{
   idt_ptr.limit = sizeof(idt_entry_t) * 256 -1;
   idt_ptr.base  = (uint32_t)&idt_entries;

   memset(&idt_entries, 0, sizeof(idt_entry_t)*256);

#define DEFINE_ISR(__n) idt_set_gate(__n, (uint32_t)isr ## __n, 0x08, 0x8E)
   DEFINE_ISR(0);
   DEFINE_ISR(1);
   DEFINE_ISR(2);
   DEFINE_ISR(3);
   DEFINE_ISR(4);
   DEFINE_ISR(5);
   DEFINE_ISR(6);
   DEFINE_ISR(7);
   DEFINE_ISR(8);
   DEFINE_ISR(9);
   DEFINE_ISR(10);
   DEFINE_ISR(11);
   DEFINE_ISR(12);
   DEFINE_ISR(13);
   DEFINE_ISR(14);
   DEFINE_ISR(15);
   DEFINE_ISR(16);
   DEFINE_ISR(17);
   DEFINE_ISR(18);
   DEFINE_ISR(19);
   DEFINE_ISR(20);
   DEFINE_ISR(21);
   DEFINE_ISR(22);
   DEFINE_ISR(23);
   DEFINE_ISR(24);
   DEFINE_ISR(25);
   DEFINE_ISR(26);
   DEFINE_ISR(27);
   DEFINE_ISR(28);
   DEFINE_ISR(29);
   DEFINE_ISR(30);
   DEFINE_ISR(31);
#undef DEFINE_ISR

   idt_flush((uint32_t)&idt_ptr);
}

static void idt_set_gate(uint8_t num, uint32_t base, uint16_t sel, uint8_t flags)
{
   idt_entries[num].base_lo = base & 0xFFFF;
   idt_entries[num].base_hi = (base >> 16) & 0xFFFF;

   idt_entries[num].sel     = sel;
   idt_entries[num].always0 = 0;
   // We must uncomment the OR below when we get to using user-mode.
   // It sets the interrupt gate's privilege level to 3.
   idt_entries[num].flags   = flags /* | 0x60 */;
}
