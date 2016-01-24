#include "interrupts.h"
#include "kb_codes.h"

void interrupts_init_pic() {
    // ICW1
    outb(PIC1_CMD_PORT, ICW1_INIT);
    outb(PIC2_CMD_PORT, ICW1_INIT);

    // ICW2, set interrupt offsets
    outb(PIC1_DATA_PORT, PIC1_OFFSET);
    outb(PIC2_DATA_PORT, PIC2_OFFSET);

    // ICW3, cascading
    // outb(PIC1_DATA_PORT, 4);        // Slave is on IRQ2 (0000 0100)
    // outb(PIC2_DATA_PORT, 2);        // Set cascade number (0000 0010)

    outb(PIC1_DATA_PORT, 0x00);
    outb(PIC2_DATA_PORT, 0x00);        // ditto


    // ICW4, 8086 mode
    outb(PIC1_DATA_PORT, ICW4_8086);
    outb(PIC2_DATA_PORT, ICW4_8086);

    // Disable all IRQ lines for now
    outb(PIC1_DATA_PORT, 0xff);
    outb(PIC2_DATA_PORT, 0xff);

    return;
}

void interrupts_init_idt() {
    uint32_t keyboard_address;
    uint32_t idt_address;
    uint32_t idt_ptr[2];
    keyboard_address = (uint32_t)keyboard_handler;

    // 0x21 here is 32 + 1. 32 is the offset, and 1 is the PIC keyboard device
    idt[0x21].handler_offset_low = keyboard_address & 0xffff;
    idt[0x21].segment_selector = KERNEL_CODE_SEGMENT_OFFSET;
    idt[0x21].unused = 0;
    idt[0x21].type = IDT_INTERRUPT_GATE;
    idt[0x21].handler_offset_high = (keyboard_address & 0xffff0000) >> 16;

    idt_address = (uint32_t) idt;
    idt_ptr[0] = (sizeof (struct interrupt_gate) * IDT_NUM_ENTRIES) + ((idt_address & 0xffff) << 16);
    idt_ptr[1] = idt_address >> 16;

    load_idt(idt_ptr);
    return;
}

void keyboard_init() {
    outb(0x21 , 0xFD);
}

void keyboard_handler_main(void) {
    unsigned char status;
    char keycode;
    char c;
    outb(PIC1_CMD_PORT, PIC1_OFFSET);   // Are these consts the correct ones?

    status = inb(KEYBOARD_STATUS_PORT);

    if (status & 0x01) {
        keycode = inb(KEYBOARD_DATA_PORT);
        if (keycode < 0) {
            return;
        }
        // Convert keycode to character
        c = kbdus[(uint8_t)keycode];
        kernel_keyboard_handler(c);

    }
}

void set_kernel_keyboard_handler(void (*f)(char)) {
    kernel_keyboard_handler = f;
}

void interrupts_init() {
    set_current_color(COLOR_WHITE, COLOR_BLACK);
    interrupts_init_pic();
    interrupts_init_idt();
    keyboard_init();
}
