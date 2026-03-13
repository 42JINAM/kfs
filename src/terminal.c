#include "kernel.h" 

t_terminal_state	g_vga;

void	scroll_down() {
	int idx;

	for (int y = 0; y < VGA_HEIGHT - 1; y++) {
		for (int x = 0; x < VGA_WIDTH; x++) {
			idx = y * VGA_WIDTH + x;
			g_vga.vga_buffer[idx] = g_vga.vga_buffer[idx + VGA_WIDTH];
		}
	}
	for (int x = 0; x < VGA_WIDTH; x++) {
		idx = (VGA_HEIGHT - 1) * VGA_WIDTH + x;
		g_vga.vga_buffer[idx] = g_vga.vga_buffer[idx + VGA_WIDTH];
	}
	update_cursor(g_vga.active->col, g_vga.active->row);
}

//put entry(character + color) at position (x, y)
void	terminal_putentryat(char c, uint8_t color, size_t x, size_t y)
{
	const size_t	idx = y * VGA_WIDTH + x;

	g_vga.vga_buffer[idx] = vga_entry(c, color);
}

void	terminal_putchar(char c)
{
	if (c == '\n') {

		g_vga.active->col = 0;
		if (++g_vga.active->row == VGA_HEIGHT) {
			g_vga.active->row = VGA_HEIGHT - 1;
			scroll_down();
			return ;
		}
	} 
	else {
		terminal_putentryat(c, g_vga.active->color, g_vga.active->col, g_vga.active->row);
		if (++g_vga.active->col == VGA_WIDTH)
		{
			g_vga.active->col = 0;
			if (++g_vga.active->row == VGA_HEIGHT) {
				g_vga.active->row = VGA_HEIGHT - 1;
				scroll_down();
			}
		}
	}
}

void	terminal_write_char(char c)
{
	terminal_putchar(c);
	update_cursor(g_vga.active->col, g_vga.active->row);
}

void	terminal_write_line(const char *data)
{
	size_t	i;

	i = 0;
	while (i < strlen(data))
	{
		terminal_putchar(data[i]);
		i ++;
	}
	update_cursor(g_vga.active->col, g_vga.active->row);
}
