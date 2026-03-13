#include "terminal.h"

// making a 8bits color code
// color (uint8_t) : 7 6 5 4 (bg color 4bits)| 3 2 1 0 (char color 4bits)
uint8_t	vga_entry_color(enum e_vga_color fg, enum e_vga_color bg)
{
	return (fg | bg << 4);
}

// making a char code (16bits)
// 1 block of VGA (2bytes): 
// 15 14 13 12(bg) | 11 10 9 8 (fg)| 7 6 5 4 3 2 1 0 (ascii)  
uint16_t	vga_entry(unsigned char uc, uint8_t color)
{
	return ((uint16_t) uc | (uint16_t) color << 8);
}


