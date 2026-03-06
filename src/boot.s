; 1. MBFLAGS 
; Declare constants for the multiboot header.
;; MBALIGN - When copying the kernel into memory, align it to the start of a page
;; MEMINFO - Scans the entire system memory map and passes it to the kernel

MBALIGN  equ  1 << 0            ; align loaded modules on page boundaries
MEMINFO  equ  1 << 1            ; provide memory map
MBFLAGS  equ  MBALIGN | MEMINFO ; this is the Multiboot 'flag' field
MAGIC    equ  0x1BADB002        ; 'magic number' lets bootloader find the header
CHECKSUM equ -(MAGIC + MBFLAGS) ; checksum of above, to prove we are multiboot
                                ; CHECKSUM + MAGIC + MBFLAGS should be Zero (0)

; Page 1: [    Kernel    | 12 bytes garbage]
; Page 2: [ 3KB garbage  |     Kernel      ]
; ↓ With MBALIGN enabled
; Page 1: [      Kernel (entire)           ]
; Page 2: [          Empty space           ]


; multiboot header 
; GRUB searches the first 8 KiB in 32-bit mode for the magic number to recognize the kernel
section .multiboot
align 4
  dd MAGIC
  dd MBFLAGS
  dd CHECKSUM
  ; dd : define double word - 4 bytes


; Stack Setup for kernel entry
section .bss
align 16
Stack_bottom:
resb 16384 ; 16 KiB
stack_top:


; kernel entry point 
section .text
global _start:function (_start.end - _start) ; declare _start function and specify its size
_start:
  ;1. setup a stack
  mov esp, stack_top
  ;1-2. etc: GDT, floating point
  ;now we can call C functions

  ;2. call kernel_main
  extern kernel_main
  call kernel_main

  ;3. kernel termination loop
  cli
.hang:  hlt
  jmp .hang
.end: