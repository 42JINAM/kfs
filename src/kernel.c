#include "kernel.h"

static uint64_t	gdt[5];
static t_gdtr	gdtr;
//
// static void	set_gdt_table(void)
// {
// 	gdt[0] = 0;
// 	gdt[1] = get_kernel_code();
// 	gdt[2] = get_kernel_data();
// 	gdt[3] = get_user_code();
// 	gdt[4] = get_user_data();
// }

static void set_gdt_table(void) {
    gdt[0] = 0;
    gdt[1] = 0x00CF9A000000FFFFULL;  // kernel_code (완벽)
    gdt[2] = 0x00CF92000000FFFFULL;  // kernel_data (완벽)
    gdt[3] = 0;
    gdt[4] = 0;
}

void	flush_gdt(void)
{
	asm volatile (
		"lgdtl (%0)		\n\t"
		"movw	$0x10, %%ax \n\t"
		"movw	%%ax, %%ds \n\t"
		"movw	%%ax, %%es \n\t"
		"movw	%%ax, %%fs \n\t"
		"movw	%%ax, %%gs \n\t"
		"movw	%%ax, %%ss \n\t"
		"ljmp $0x08, $2f\n\t"
		"2:				\n\t"
		: : "r" (&gdtr) :"ax", "cc", "memory"
	);
}

void	init_gdt(void)
{
	set_gdt_table();
	gdtr.limit = sizeof(gdt) - 1;
	gdtr.base = (uint32_t)(uintptr_t)gdt;
	flush_gdt();
}

void	kernel_main(void)
{
	init_gdt();
	g_vga.vga_buffer = (uint16_t *)VGA_MEMORY;
	print_ascii();
	terminal_initialize();
	terminal_write_line("hello 42 world!\n");

	// test_printf();

	keyboard_handler();
    while (1) {
        asm volatile ("hlt");  // CPU 대기 → 무한 루프!
    }
}

