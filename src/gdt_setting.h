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

// gdt access

#define GDT_CODE_KERNEL    0x9A  // P=1,DPL=0,S=1,Code/Read
#define GDT_DATA_KERNEL    0x92  // P=1,DPL=0,S=1,Data/Write
#define GDT_CODE_USER      0xFA  // P=1,DPL=3,S=1,Code/Read
#define GDT_DATA_USER      0xF2  // P=1,DPL=3,S=1,Data/Write
// granularity

#define GDT_GRAN_32BIT     0xCF  // G=1(4GB),D=1(32bit),L=0,AVL=1
// limit
#define GDT_LIMIT_4GB      0xFFFFF

//gdt entry
typedef struct __attribute__((packed)) {
    uint16_t limit_low;    // 0-15
    uint16_t base_low;     // 16-31
    uint8_t  base_mid;     // 32
    uint8_t  access;       // 33-40 (type+S+DPL+P)
    uint8_t  gran;         // 41-48 (limit_high+flags)
    uint8_t  base_high;    // 49-56
} gdt_entry_t;  //

//gdtr
typedef struct __attribute__((packed)) s_gdtr
{
	uint16_t	limit;
	uint32_t	base;
}	t_gdtr;

void	    init_gdt(void);
//
// static void print_gdt_entry(unsigned i);
// static void print_gdt(void);
//
extern gdt_entry_t	gdt[5];
extern t_gdtr	gdtr;
#endif // !GDT_SETTING_H
