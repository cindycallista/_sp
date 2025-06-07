    .globl mul3
    .text

mul3:
    pushl %ebp
    movl %esp, %ebp

    movl 8(%ebp), %eax
    imull 12(%ebp), %eax
    imull 16(%ebp), %eax

    popl %ebp
    ret
