section .data

    msg1: db "Enter the string : "
    size1: equ $-msg1

    isPal: db "The string is palindrome",10
    pal: equ $-isPal

    notPal: db "The string is not a palindrome",10
    npal: equ $-notPal

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

    check:

        cmp r9, r8
        jnb isP

        mov al, byte[r8]
        mov bl, byte[r9]

        cmp al, bl
        jne notP 

        inc r9
        dec r8

        jmp check

    isP:

        mov rax, 4
        mov rbx, 1
        mov rcx, isPal
        mov rdx, pal
        int 80h
        jmp end_s

    notP:

        mov rax, 4
        mov rbx, 1
        mov rcx, notPal
        mov rdx, npal
        int 80h
        jmp end_s
    
    end_s:

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



        



