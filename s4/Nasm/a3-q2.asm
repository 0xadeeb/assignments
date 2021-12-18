section .data

    msg1: db "Enter the string : "
    size1: equ $-msg1

    msg2: db "Reverse of the string: "
    size2: equ $-msg2

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

    dec r8
    mov r9, string

    mov rax, 4
    mov rbx, 1
    mov rcx, msg2
    mov rdx, size2
    int 80h

    print_s:

        cmp r8, r9
        jb end_s
        
        mov al, byte[r8]
        mov byte[c], al

        mov rax, 4
        mov rbx, 1
        mov rcx, c
        mov rdx, 1
        int 80h

        dec r8
        jmp print_s

    end_s:
        
        mov rax, 4
        mov rbx, 1
        mov rcx, nl
        mov rdx, 1
        int 80h

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
        


        