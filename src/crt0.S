.global _start
.type _start, @function
_start:
    call main
    mov %rax, %rdi      
    call _exit
    hlt
