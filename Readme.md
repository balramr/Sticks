# Sticks
Sticks is the result of my very first experiments in OS kernel development. Once loaded by the bootloader, it displays a message on the terminal. It has rudementry support for keyboard input, displaying entered characters on the terminal and moving the cursor.

Sticks is written in C, with a small amount of assembler (NASM).

## Building
Sticks requires GCC and nasm. For GCC, I used a cross compiling i686 version that I built using the OSDev guide (see below).

The Makefile also expects i686-elf-gcc to be available on the path. For example, if the binary is available under `/opt/crossgcc`, set `PATH` accordingly:

```
export PREFIX="/opt/crossgcc"
export PATH="$PREFIX/bin:$PATH"
````

The Makefile also expects QEMU (`qemu-system-i386`) for running, and executes the ELF binary directly. In theory, Sticks could work with Bochs, VirtualBox, or maybe even on real hardware, but this has not been tested. Building an ISO will require an extra step.

## Resources
Sticks was written with help from many online resources. Some of them are:

* [OSDev Bare Bones](http://wiki.osdev.org/Bare_Bones) - a good way to get started
* [Intel 80386 Programmer's Reference Manual](css.csail.mit.edu/6.858/2015/readings/i386.pdf) - while the latest version of this guide will have the same information, this 1986 version is more brief and accesible 
* OSDev's [Interrupts](http://wiki.osdev.org/Interrupts) and [PIC](http://wiki.osdev.org/8259_PIC) pages to implement interrupt handling (for keyboard input)
* [Intel 8259A PIC guide](https://pdos.csail.mit.edu/6.828/2010/readings/hardware/8259A.pdf) - a fairly low level spec for the PIC
* ["Kernel 201 - Let’s write a Kernel with keyboard and screen support"](http://arjunsreedharan.org/post/99370248137/kernel-201-lets-write-a-kernel-with-keyboard) - a simple example that implements keyboard input
* [Keyboard mapping code](http://www.osdever.net/bkerndev/Docs/keyboard.htm) - a header file for mapping scancodes to ASCII characters

## License
Sticks is available in the public domain. See COPYING.