#ifndef KERNEL_H
# define KERNEL_H 

# include "terminal.h"
# include "keyboard.h"
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

#endif /* KERNEL_H */
