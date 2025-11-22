.text
    .globl syscall3

syscall3:
    movq %rdi, %rax
    movq %rsi, %rdi
    movq %rdx, %rsi
    movq %rcx, %rdx
    syscall
    ret

    .globl syscall6

syscall6:
    movq %rdi, %rax      # syscall number
    movq %rsi, %rdi      # arg1
    movq %rdx, %rsi      # arg2
    movq %rcx, %rdx      # arg3
    movq %r8, %r10       # arg4
    movq %r9, %r8        # arg5
    movq 8(%rsp), %r9    # arg6 (from stack)
    syscall
    ret


    .globl syscall
syscall:
    jmp syscall6


.section .note.GNU-stack,"",@progbits
