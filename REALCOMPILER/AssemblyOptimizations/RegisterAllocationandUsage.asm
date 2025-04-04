section .data
    result db 0      ; Allocate a byte for result

section .text
    global _start

_start:
    mov rax, 5        ; Load immediate value into register
    mov rbx, 3        ; Load another value
    add rax, rbx      ; Perform addition using registers
    mov [result], rax ; Store result in memory

    ; Exit
    mov rax, 60       ; Syscall number for exit
    xor rdi, rdi      ; Exit status 0
    syscall

