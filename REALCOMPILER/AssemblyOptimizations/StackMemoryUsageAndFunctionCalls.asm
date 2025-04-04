my_function:
    push rbp          ; Save base pointer
    mov rbp, rsp      ; Create stack frame
    
    ; Function body (e.g., arithmetic operations)
    mov rax, [rbp+8]  ; Load function argument from stack
    
    pop rbp           ; Restore base pointer
    ret               ; Return to caller
