        .global _start

        .text
_start:
        # write(1, message, 13)
        lea 16(%rsp),%rdi        # system call 1 is write
        ret