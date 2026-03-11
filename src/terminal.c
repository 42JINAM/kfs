#include "kernel.h" 

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

void	set_background(uint16_t* buffer, uint16_t entry) {
	int idx;

	for (int y = 0; y < VGA_HEIGHT; y++) {
		for (int x = 0; x < VGA_WIDTH; x++) {
			idx = y * VGA_WIDTH + x;
			buffer[idx] = entry;
		}
	}
}
void	set_terminal(t_terminal *t, uint16_t color)
{
	t->col = 0;
	t->row = 0;
	t->color = color;
	set_background(t->buffer, vga_entry(' ', color));
}

void	terminal_initialize(void)
{
	set_terminal(&g_vga.t1, vga_entry_color(VGA_COLOR_LIGHT_GREY, VGA_COLOR_BLACK));
	set_terminal(&g_vga.t2, vga_entry_color(VGA_COLOR_LIGHT_RED, VGA_COLOR_RED));
	flush_terminal(&g_vga.t1);
	g_vga.t1_switch = true;
}

void	terminal_setcolor(uint8_t color)
{
	g_vga.active->color = color;
}

void	scroll_down() {
	int idx;

	for (int y = 0; y < VGA_HEIGHT - 1; y++) {
		for (int x = 0; x < VGA_WIDTH; x++) {
			idx = y * VGA_WIDTH + x;
			g_vga.active->buffer[idx] = g_vga.active->buffer[idx + VGA_WIDTH];
		}
	}
	for (int x = 0; x < VGA_WIDTH; x++) {
		idx = (VGA_HEIGHT - 1) * VGA_WIDTH + x;
		g_vga.active->buffer[idx] = g_vga.active->buffer[idx + VGA_WIDTH];
	}
	update_cursor(g_vga.active->col, g_vga.active->row);
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

void	backup_terminal(t_terminal *t)
{
    memcpy(t->buffer, g_vga.vga_buffer, VGA_WIDTH * VGA_HEIGHT * 2);
}

void    flush_terminal(t_terminal *t)
{
    g_vga.active = t;
    memcpy(g_vga.vga_buffer, t->buffer, VGA_WIDTH * VGA_HEIGHT * 2);

	update_cursor(g_vga.active->col, g_vga.active->row);
}
