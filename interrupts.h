#ifndef INTERRUPTS_H
#define INTERRUPTS_H

#include "terminal.h"

#include <stdint.h>

#define IDT_NUM_ENTRIES 256
#define IDT_KEYBOARD_POS 0x21   // 32 + 1

#define IDT_INTERRUPT_GATE 0x8e     // refer to Intel manual/osdev

#define KERNEL_CODE_SEGMENT_OFFSET 0x08    // in GDT

#define PIC1_CMD_PORT 0x20
#define PIC1_DATA_PORT 0x21
#define PIC2_CMD_PORT 0xA0
#define PIC2_DATA_PORT 0xA1

// Interrupts start from 32d
#define PIC1_OFFSET 0x20
#define PIC2_OFFSET 0x28

#define ICW1_INIT 0x11
#define ICW4_8086 0x01

#define KEYBOARD_DATA_PORT  0x60
#define KEYBOARD_STATUS_PORT  0x64



// Defined in boot.asm
extern void outb(uint16_t port, uint8_t out);
extern uint8_t inb(uint16_t port);
extern void keyboard_handler();
extern void load_idt(unsigned long *idt_ptr);

struct interrupt_gate {
    uint16_t    handler_offset_low;
    uint16_t    segment_selector;
    uint8_t     unused;
    uint8_t     type;
    uint16_t    handler_offset_high;
} __attribute__((packed));

struct interrupt_gate idt[IDT_NUM_ENTRIES];

void (*kernel_keyboard_handler)(char);

void interrupts_init();
void set_kernel_keyboard_handler(void (*f)(char));
void interrupts_init_pic();

#endif
