section .data

    msg1: db "Enter the first string : "
    size1: equ $-msg1

    msg2: db "Enter the second string : "
    size2: equ $-msg2
    
    msg3: db "The strings are similar ", 10
    size3: equ $-msg3

    msg4: db "The strings are dissimilar at position ", 
    size4: equ $-msg4

    nl: db 10

section .bss

    string1: resb 100
    string2: resb 100
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
    mov r8, string1 
    call scan_string

    mov rax, 4
    mov rbx, 1
    mov rcx, msg2
    mov rdx, size2
    int 80h

    mov r8, string2
    call scan_string

    mov r8, string1
    mov r9, string2
    mov byte[strlen], 31h

    check:

        mov al, byte[r8]
        mov bl, byte[r9]

        cmp al, bl
        jne notEq

        cmp al, 0
        je Eq 

        inc r8
        inc r9
        inc byte[strlen]

        jmp check

    Eq:

        mov rax, 4
        mov rbx, 1
        mov rcx, msg3
        mov rdx, size3
        int 80h

        mov rax, 1
        mov rbx, 0
        int 80h

    notEq:

        mov rax, 4
        mov rbx, 1
        mov rcx, msg4
        mov rdx, size4
        int 80h

        mov rax, 4
        mov rbx, 1
        mov rcx, strlen
        mov rdx, 1
        int 80h

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





    

