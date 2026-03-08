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
///
// TODO : support for line breaks('\n')
// TODO:: support for scrolling
//
void	kernel_main(void)
{
	terminal_initialize();
	terminal_write_line("42 hello");
	terminal_write_line("42 bye");
}
