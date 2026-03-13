#include "kernel.h" 

void	backup_terminal(t_tab *t)
{
    memcpy(t->buffer, g_vga.vga_buffer, VGA_WIDTH * VGA_HEIGHT * 2);
}

void  flush_terminal(t_tab *t)
{
    g_vga.active = t;
    memcpy(g_vga.vga_buffer, t->buffer, VGA_WIDTH * VGA_HEIGHT * 2);
	update_cursor(g_vga.active->col, g_vga.active->row);
}
