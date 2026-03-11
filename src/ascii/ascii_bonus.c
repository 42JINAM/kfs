#include "ascii.h"
#include "../kernel.h"

void	logo(void)
{
	printf(" 42 42 42");
	printf("\n");
}

void	erase_ascii(void)
{
	set_background(g_vga.vga_buffer, vga_entry(' ', g_vga.active->color));
	g_vga.active->col = 0;
	g_vga.active->row = 0;
	update_cursor(g_vga.active->col, g_vga.active->row);
}

static void	busy_wait(unsigned int count)
{
	volatile unsigned int	delay;

	delay = 0;
	while (delay < count)
		delay++;
}

void	print_ascii(void)
{
	const t_ascii_func	draw[25] = {\
		ascii_1, ascii_2, ascii_3, ascii_4, ascii_5, ascii_6, ascii_7, \
		ascii_8, ascii_9, ascii_10, ascii_11, ascii_12, ascii_13, ascii_14, \
		ascii_15, ascii_16, ascii_17, ascii_18, ascii_19, ascii_20, ascii_21, \
		ascii_22, ascii_23, ascii_24, ascii_25
	};
	int					i;

	set_terminal(&g_vga.t1, vga_entry_color(VGA_COLOR_LIGHT_GREEN, VGA_COLOR_BLACK));
	flush_terminal(&g_vga.t1);
	i = 0;
	while (i < 25)
	{
		erase_ascii();
		draw[i]();
		busy_wait(80000000);
		i++;
	}
}