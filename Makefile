LD=i686-elf-gcc
CC=i686-elf-gcc
NASM=nasm
QEMU=qemu-system-i386
COBJ = kernel.o interrupts.o terminal.o

all: sticks.bin

%.o: %.c
	$(CC) -c $< -o $@ -std=gnu99 -ffreestanding -O2 -Wall -Wextra

boot.o: boot.asm
	$(NASM) -f elf -o $@ $<

sticks.bin: $(COBJ) boot.o
	$(LD) -T linker.ld -o $@ -ffreestanding -O2 -nostdlib $^ -lgcc


run: sticks.bin
	$(QEMU) -kernel $<
