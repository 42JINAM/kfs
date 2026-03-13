#ifndef KERNEL_H
# define KERNEL_H 
# include "terminal.h"
# include "ascii/ascii.h"
# include "utils/utils.h"

# include <limits.h>
# include <stdbool.h>
# include <stdarg.h>
# include <stdint.h>

//
/* Check if the compiler thinks you are targeting the wrong operating system. */
// # if defined(__linux__)
// 	#error "You are not using a cross-compiler."
// # endif
//
// /* This tutorial will only work for the 32-bit ix86 targets. */
// # if !defined(__i386__)
// 	#error "This tutorial needs to be compiled with a ix86-elf compiler"
// # endif

// typedef unsigned char		uint8_t;
// typedef unsigned short int	uint16_t;
// typedef unsigned int		    uint32_t;
// typedef unsigned long		size_t;

// https://wiki.osdev.org/Inline_Assembly/Examples#OUTx
static inline void outb(uint16_t port, uint8_t val)
{
    __asm__ volatile ( "outb %b0, %w1" : : "a"(val), "Nd"(port) : "memory");
    /* There's an outb %al, $imm8 encoding, for compile-time constant port numbers that fit in 8b. (N constraint).
     * Wider immediate constants would be truncated at assemble-time (e.g. "i" constraint).
     * The  outb  %al, %dx  encoding is the only option for all other cases.
     * %1 expands to %dx because  port  is a uint16_t.  %w1 could be used if we had the port number a wider C type */
}

static inline uint8_t inb(uint16_t port)
{
    uint8_t ret;
    __asm__ volatile ( "inb %w1, %b0"
                   : "=a"(ret)
                   : "Nd"(port)
                   : "memory");
    return ret;
}

void keyboard_handler();

#endif /* KERNEL_H */
