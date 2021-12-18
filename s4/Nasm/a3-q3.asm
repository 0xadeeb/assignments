section .data

    msg1: db "Enter the first string : "
    size1: equ $-msg1

    msg2: db "Enter the second string : "
    size2: equ $-msg2
    
    msg3: db "The concatinated string is: "
    size3: equ $-msg3

    nl: db 10

section .bss

    string: resb 100
    c: resb 1
    strlen: resb 1

section .text

global _start

_start:

    mov rax, 4
    mov rbx, 1
    mov rcx, msg1
    mov rdx, size1
    int 80h

    mov byte[strlen], 0
    mov r8, string 
    call scan_string

    mov rax, 4
    mov rbx, 1
    mov rcx, msg2
    mov rdx, size2
    int 80h

    call scan_string

    mov r8, string

    mov rax, 4
    mov rbx, 1
    mov rcx, msg3
    mov rdx, size3
    int 80h

    call print_string

    mov rax, 1
    mov rbx, 0
    int 80h

scan_string:

    read:

        mov rax, 3
        mov rbx, 0
        mov rcx, c
        mov rdx, 1
        int 80h

        cmp byte[c], 10
        je end

        inc byte[strlen]
        mov al, byte[c]
        mov byte[r8], al
        inc r8

        jmp read

    end:

        mov byte[r8], 0
        ret  

print_string:

    print_s:

        mov al, byte[r8]
        mov byte[c], al

        cmp byte[c], 0
        je end_p

        mov rax, 4
        mov rbx, 1
        mov rcx, c 
        mov rdx, 1
        int 80h

        inc r8

        jmp print_s

    end_p:

        mov rax, 4
        mov rbx, 1
        mov rcx, nl
        mov rdx, 1
        int 80h   

        ret