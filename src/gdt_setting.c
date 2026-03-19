#include "kernel.h"

gdt_entry_t	gdt[5];
t_gdtr	gdtr;

void	set_gdt_entry(gdt_entry_t *e, uint32_t base, uint32_t limit, uint8_t access, uint8_t gran)
{
	e->limit_low = limit & 0xFFFF;
	e->base_low = base & 0xFFFF;
	e->base_mid = (base >> 16) & 0xFF;
	e->access = access;
	e->gran = (uint8_t)(limit >> 16) & 0x0F;
	e->gran |= (uint8_t)(gran &0xF0);
	e->base_high = (base >> 24) & 0xFF;

}

static void set_gdt_table(void) {
	
    // gdt[0] = 0;
    // gdt[1] = 0x00CF9A000000FFFFULL;  // kernel_code (완벽)
    // gdt[2] = 0x00CF92000000FFFFULL;  // kernel_data (완벽)
    // gdt[3] = 0;
    // gdt[4] = 0;
    
    memset(gdt, 0, sizeof(gdt));
    set_gdt_entry(&gdt[1], 0, GDT_LIMIT_4GB, GDT_CODE_KERNEL, GDT_GRAN_32BIT);
    set_gdt_entry(&gdt[2], 0, GDT_LIMIT_4GB, GDT_DATA_KERNEL, GDT_GRAN_32BIT);
    set_gdt_entry(&gdt[3], 0, GDT_LIMIT_4GB, GDT_CODE_USER, GDT_GRAN_32BIT);
    set_gdt_entry(&gdt[4], 0, GDT_LIMIT_4GB, GDT_DATA_USER, GDT_GRAN_32BIT);
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
