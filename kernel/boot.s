KERNEL_STACK_SIZE equ 4096
MAGIC_NUMBER      equ 0x1BADB002
FLAGS             equ 0x0
CHECKSUM          equ -MAGIC_NUMBER

extern __kernel_entry

section .bss
align 4
kernel_stack:
  resb KERNEL_STACK_SIZE

section .text
align 4
  dd MAGIC_NUMBER
  dd FLAGS
  dd CHECKSUM

global __entry
__entry:
  ; Sets the stack pointer
  mov   esp,    kernel_stack + KERNEL_STACK_SIZE    ; ESP = End of stack

  ; Jumps to the kernel
  jmp   __kernel_entry
loop:
  jmp   loop