    .text
    .global _start
    .type _start, @function
_start:
    xor %rbp, %rbp

    call main

.halt_loop:
    pause
    jmp .halt_loop
