#include "kernel.h"

// this kernel uses the VGA text mode buffer as the output device.
//
// Why kernel.c can't use standard C libray functions:
// 1. libc depends on our os and
// 2. kernel is SERVICE PROVIDER not consumer.
//	- kernel role: IMPLEMENT printf for userspace. 
//	- USER role: CALL printf
// 3. Kernel has only raw resauces
//	- No syscalls implemented yet
//	- Direct physical memory.
//	- No any (?) interface for userside (malloc, printf, fopen, ...)
//

void test_printf(void) {
	int a = 1;
	int b = 2;

	char c = 'c';
	char d = 'd';
	printf("printf c: %c\n", 'c');
	printf("printf s: %s\n", "string");
	
	printf("int a ==========\n");
	printf("printf p: %p \n", a);
	printf("printf x: %x \n", a);
	printf("printf X: %X \n", a);
		
	printf("int b ==========\n");
	printf("printf p: %p \n", b);
	printf("printf x: %x \n", b);
	printf("printf X: %X \n", b);

	printf("char c ==========\n");
	printf("printf p: %p \n", c);
	printf("printf x: %x \n", c);
	printf("printf X: %X \n", c);
	
	printf("char d ==========\n");
	printf("printf p: %p \n", d);
	printf("printf x: %x \n", d);
	printf("printf X: %X \n", d);

}

void	kernel_main(void)
{
	g_vga.vga_buffer = (uint16_t *)VGA_MEMORY;
	print_ascii();
	terminal_initialize();
	terminal_write_line("42 hello\n");
	
	// test_printf();

	keyboard_handler();
}
