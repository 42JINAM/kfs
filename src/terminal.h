#ifndef TERMINAL_H
# define TERMINAL_H

# include <stdbool.h>
# include <stddef.h>
# include <stdint.h>
# include "string.h"

/* VGA Hardware Text mode (80 * 25 color text mode) */
# define VGA_WIDTH	80
# define VGA_HEIGHT	25	
# define VGA_MEMORY	0xB8000

/* Hardware text mode color constants. */
enum e_vga_color
{
	VGA_COLOR_BLACK = 0,
	VGA_COLOR_BLUE = 1,
	VGA_COLOR_GREEN = 2,
	VGA_COLOR_CYAN = 3,
	VGA_COLOR_RED = 4,
	VGA_COLOR_MAGENTA = 5,
	VGA_COLOR_BROWN = 6,
	VGA_COLOR_LIGHT_GREY = 7,
	VGA_COLOR_DARK_GREY = 8,
	VGA_COLOR_LIGHT_BLUE = 9,
	VGA_COLOR_LIGHT_GREEN = 10,
	VGA_COLOR_LIGHT_CYAN = 11,
	VGA_COLOR_LIGHT_RED = 12,
	VGA_COLOR_LIGHT_MAGENTA = 13,
	VGA_COLOR_LIGHT_BROWN = 14,
	VGA_COLOR_WHITE = 15,
};

typedef struct s_terminal
{
	size_t		row;
	size_t		col;
	uint8_t		color;
	uint16_t	buffer[VGA_WIDTH * VGA_HEIGHT * 2];
} t_terminal;

/* Terminal state struct */
typedef struct s_terminal_state
{
	bool		t1_switch;
	uint16_t	*vga_buffer;
	t_terminal	*active;
	t_terminal	t1;
	t_terminal	t2;
}	t_terminal_state;


void		set_terminal(t_terminal *t, uint16_t color);
void		set_background(uint16_t* buffer, uint16_t entry);
void		terminal_initialize(void);
void		terminal_setcolor(uint8_t color);
void		terminal_putentryat(char c, uint8_t color, size_t x, size_t y);
void		terminal_putchar(char c);

void		terminal_write_char(char c);
void		terminal_write_line(const char *data);

void		backup_terminal(t_terminal *t);
void    	flush_terminal(t_terminal *t);

uint8_t		vga_entry_color(enum e_vga_color fg, enum e_vga_color bg);
uint16_t	vga_entry(unsigned char uc, uint8_t color);

extern t_terminal_state	g_vga;
#endif // !TERMINAL_H
