#include "terminal.h"

uint8_t terminal_current_color;
uint16_t* terminal_buffer = (uint16_t*) 0xB8000;
uint8_t terminal_width = 80;
uint8_t terminal_height = 25;

uint8_t cur_x = 0;
uint8_t cur_y = 0;

uint16_t make_colored_char(char c, uint8_t encoded_color) {
    return (uint16_t)c | encoded_color << 8;
}

uint16_t make_char(char c) {
    return make_colored_char(c, terminal_current_color);
}

void set_current_color(enum vga_color fg, enum vga_color bg) {
    terminal_current_color = (uint16_t)fg | (uint16_t)bg << 4;
}

void reset_current_color() {
    set_current_color(COLOR_WHITE, COLOR_BLACK);
}

void place_cursor(size_t terminal_pos) {
    outb(0x3D4, 14);
    outb(0x3D5, terminal_pos >> 8);
    outb(0x3D4, 15);
    outb(0x3D5, terminal_pos);
}


size_t terminal_pos(uint8_t x, uint8_t y) {
    return y * terminal_width + x;
}

void set_cursor(uint8_t x, uint8_t y) {
    place_cursor(terminal_pos(x, y));
}

void update_cursor() {
    place_cursor(terminal_pos(cur_x, cur_y));
}

void put_char(char c) {
    size_t pos = cur_y * terminal_width + cur_x;
    if(c == '\n') {
        cur_x = 0;
        if (cur_y != (terminal_height - 1)) {
            cur_y += 1;
        }
    }
    else {
        terminal_buffer[pos] = make_char(c);
        if (cur_x == (terminal_width - 1)) {
            cur_x = 0;
            if (cur_y != (terminal_height -1)) {
                cur_y += 1;
            }
        }
        else {
            cur_x ++;
        }
    }
    update_cursor();
}

void put_string(char *str) {
    uint16_t i = 0;
    char c = str[i];
    while (c != '\0') {
        put_char(c);
        c = str[++i];
    }
}


void terminal_init() {
    reset_current_color();
	for (size_t y = 0; y < terminal_height; y++) {
		for (size_t x = 0; x < terminal_width; x++) {
			const size_t pos = y * terminal_width + x;
			terminal_buffer[pos] = make_char(' ');
		}
	}
    cur_x = 0;
    cur_y = 0;
    update_cursor();
}
