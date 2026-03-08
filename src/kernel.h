#ifndef KERNEL_H
# define KERNEL_H 
# include "terminal.h"
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
//
//
//
//
/* 함수 선언 */
void update_cursor(int x, int y);

#endif /* KERNEL_H */
