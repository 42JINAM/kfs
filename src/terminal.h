#ifndef TERMINAL_H
# define TERMINAL_H

# include <stdbool.h>
# include <stddef.h>
# include <stdint.h>

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
enum e_current_tab 
{
	TAB_1,
	TAB_2
};

typedef struct s_tab
{
	size_t		row;
	size_t		col;
	uint8_t		color;
	uint16_t	buffer[VGA_WIDTH * VGA_HEIGHT * 2];
} t_tab;

typedef struct s_terminal
{
	enum e_current_tab	current_tab;
	uint16_t			*vga_buffer;
	t_tab				*active;
	t_tab				t1;
	t_tab				t2;
}	t_terminal;

static inline void outb(uint16_t port, uint8_t val)
{
    __asm__ volatile ( "outb %b0, %w1" : : "a"(val), "Nd"(port) : "memory");
    /* There's an outb %al, $imm8 encoding, for compile-time constant port numbers that fit in 8b. (N constraint).
     * Wider immediate constants would be truncated at assemble-time (e.g. "i" constraint).
     * The  outb  %al, %dx  encoding is the only option for all other cases.
     * %1 expands to %dx because  port  is a uint16_t.  %w1 could be used if we had the port number a wider C type */
}

// vga.c
uint8_t		vga_entry_color(enum e_vga_color fg, enum e_vga_color bg);
uint16_t	vga_entry(unsigned char uc, uint8_t color);

// terminal.c
void		update_cursor(int x, int y);
void		terminal_write_char(char c);
void		terminal_write_line(const char *data);

// init.c
void		init_terminal(t_tab *t, uint16_t color);
void		terminal_initialize(void);

// switch_tab.c
void		backup_terminal(t_tab *t);
void    	flush_terminal(t_tab *t);

extern t_terminal	g_vga;
#endif // !TERMINAL_H
