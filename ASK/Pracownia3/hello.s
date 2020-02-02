read = 0
write = 1
exit  = 60
.section .data
    .global _start
    .type _start, @function
    .section .text

_start: 
    movq $read, %rax
    movq $0, %rdi
    movq %rsp, %rsi
    movq $500, %rdx
    syscall

    movq %rax, %r8
    lea (%rsp, %r8), %r9

    movq $write, %rax
    movq $1, %rdi
    movq $1, %rdx
L1:
    lea -1(%r9), %r9
    movq %r9, %rsi
    syscall
    cmp %r9, %rsp
    jb L1

    movq    $exit, %rax
    movq    $0, %rdi
    syscall
        
    .size   _start, . - _start
    