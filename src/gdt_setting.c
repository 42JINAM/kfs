#include "gdt_setting.h"


// segement descriptors 
uint64_t	get_kernel_code(void)
{
	uint64_t	kernel_code = 0;

	kernel_code |= 0xFFFFULL; // limit 15 : 0
	kernel_code |= 0xF << 16; // limit 19 : 16

	kernel_code |= 0b10011010ULL	<< 40; // type (execute/read, accessed)
	kernel_code |= 1ULL		<< 44; // S= 1 not a system descriptor
	kernel_code |= 0ULL		<< 45; // DPL field = 0 (ring 0)
	kernel_code |= 1ULL		<< 47; // P = 1 present
	kernel_code |= 0ULL		<< 53; // long-mode
	kernel_code |= 1ULL		<< 54; // D/B = 1 (32bit protected mode)
	kernel_code |= 1ULL		<< 55; // G = 1 (32bit protected mode)
	
	return(kernel_code);
}

uint64_t	get_kernel_data(void)
{
	uint64_t	kernel_data = 0;

	kernel_data |= 0xFFFFULL; // limit 15 : 0
	kernel_data |= 0xF << 16; // limit 19 : 16

	kernel_data |= 0b10010010ULL	<< 40; // type (execute/read, accessed)
	kernel_data |= 1ULL	<< 44; // S= 1 not a system descriptor
	kernel_data |= 0ULL		<< 45; // DPL field = 0 (ring 0)
	kernel_data |= 1ULL		<< 47; // P = 1 present
	
	kernel_data |= 0ULL		<< 53; // long-mode
	kernel_data |= 1ULL		<< 54; // D/B = 1 (32bit protected mode)
	kernel_data |= 1ULL		<< 55; // G = 1 (32bit protected mode)

	return (kernel_data);
}

uint64_t	get_user_code(void)
{
	uint64_t	user_code = get_kernel_code() | (3 << 13);
	
	return (user_code);
}

uint64_t	get_user_data(void)
{
	uint64_t	user_data = get_kernel_data() | (3 << 13);
	
	return (user_data);
}


