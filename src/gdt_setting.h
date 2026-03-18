#ifndef GDT_SETTING_H
# define GDT_SETTING_H

#include <stdint.h>
//selectors 
#define NULL_SELECTOR 0x00
#define KERNEL_CS 0x08
#define KERNEL_DS 0x10
#define USER_CS 0x1B
#define USER_DS 0x23

#define NUM_GDT_ENTRIES 5

//gdtr
typedef struct __attribute__((packed)) s_gdtr
{
	uint16_t	limit;
	uint32_t	base;
}	t_gdtr;

uint64_t	get_kernel_code(void);
uint64_t	get_kernel_data(void);
uint64_t	get_user_code(void);
uint64_t	get_user_data(void);

#endif // !GDT_SETTING_H
