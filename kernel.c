#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

#include "terminal.h"
#include "interrupts.h"


void keyboard_input(char c) {
		char a = c;
		if (a == 0) {
			a = a - 1;
		}
		put_char(c);
}

void kernel_main() {
    terminal_init();
	put_string("Hello World, enter your stuff:\n");
	set_kernel_keyboard_handler(keyboard_input);
    interrupts_init();

}
