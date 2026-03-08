#include "terminal.h"

// terminal state variable
t_terminal_state	g_vga;
/*
 * Global terminal state -
 * every function needs to know :
 * - Where to print
 * - What color to use 
 *   하지만 매개변수로 전달도 가능하긴 해 ...
*/
// Reset cursor to (0, 0)
// set up default color(fg, bg)
// fill the screen

void	terminal_initialize(void)
{
	int	x;
	int	y;
	int	idx;

	g_vga.buffer = (uint16_t *)0xB8000;
	g_vga.row = 0;
	g_vga.col = 0;
	g_vga.color = vga_entry_color(VGA_COLOR_LIGHT_GREY, VGA_COLOR_BLACK);
	y = 0;
	while (y < VGA_HEIGHT)
	{
		x = 0;
		while (x < VGA_WIDTH)
		{
			idx = y * VGA_WIDTH + x;
			g_vga.buffer[idx] = vga_entry(' ', g_vga.color);
			x ++;
		}
		y ++;
	}
}

void	terminal_setcolor(uint8_t color)
{
	g_vga.color = color;
}

void	terminal_putchar(char c)
{
	terminal_putentryat(c, g_vga.color, g_vga.col, g_vga.row);
	if (++g_vga.col == VGA_WIDTH)
	{
		g_vga.col = 0;
		if (++g_vga.row == VGA_HEIGHT)
			g_vga.row = 0;
	}
}

void terminal_put_newline()
{
  g_vga.col = g_vga.col++;
  g_vga.row = 0;
	terminal_putentryat('\n', g_vga.color, g_vga.col, g_vga.row);
}

void	terminal_write(const char *data, size_t size)
{
	size_t	i;

	i = 0;
	while (i < size)
	{
		terminal_putchar(data[i]);
		i ++;
	}
  terminal_put_newline();
}

void	terminal_write_line(const char *data)
{
	terminal_write(data, strlen(data));
}
