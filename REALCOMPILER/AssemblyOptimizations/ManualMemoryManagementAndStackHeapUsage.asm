section .bss
    buffer resb 64   ; Reserve 64 bytes in uninitialized data section

section .text
_start:
    mov rsi, buffer  ; Load buffer address into register
    mov byte [rsi], 0 ; Initialize buffer with null terminator
    
    ; Further memory operations...
