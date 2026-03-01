; constants 
	;;1. MBFLAGS 
MBALIGN equ 1 << 0 
MEMINFO equ 1 << 1
MBFLAGS equ MBALIGN | MEMINFO
		;; MBALIGN - 커널을 메모리에 복사할 때 페이지 시작점에 정렬되게 올림 

		; 페이지 1: [    커널    | 12바이트 쓰레기]
		; 페이지 2: [3KB 쓰레기  |     커널     ]
		; ↓ MBALIGN 설정
		; 페이지 1: [    커널(전체)     ]
		; 페이지 2: [          빈 공간         ]

		;; MEMINFO - 시스템 전체 메모리맵을 조사 해서 커널에 전달함 

	;; 2. MAGIC NUMBER 
MAGIC equ 0x1BADB002

	;; 3. CHECKSUM
CHECKSUM equ -(MAGIC + MBFLAGS)

; multiboot header 
section .multiboot
align 4
		dd MAGIC
		dd MBFLAGS
		dd CHECKSUM
		; dd : define double word - 4bytes 
; GRUB이 32-bit -> 앞 8kib 에서 magic 을 찾아서 인식 

; Stack Setup for kernel entry
section .bss
align 16
Stack_bottom:
resb 16384 ; 16KiB
stack_top:


; kernel entry point 
section .text
global _start:function (_start.end - _start) ;_start 함수 선언, 크기 지정
_start:
	;1. setup a stack
	mov esp, stack_top
	;1-2. etc GDT, floating point .... 
	;아무튼 이제 C 함수를 부를 수 있음
	;2. call kernel_main
	extern kernel_main
	call kernel_main

	;3. kernel termination loop
	cli
.hang: hlt
	jmp .hang
.end:

