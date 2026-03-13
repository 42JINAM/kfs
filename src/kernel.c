#include "kernel.h"

void	kernel_main(void)
{
	g_vga.vga_buffer = (uint16_t *)VGA_MEMORY;

	print_ascii();
	terminal_initialize();
	terminal_write_line("hello 42 world!\n");
	
	// test_printf();

	keyboard_handler();
}
