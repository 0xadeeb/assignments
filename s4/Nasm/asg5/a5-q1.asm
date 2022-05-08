section .data

    msg1: db "Enter the string : "
    size1: equ $-msg1

    space: db 20h

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

    mov r9, r8

    prnt:

        cmp r9, string
        jb end

        mov al, byte[r9]
        cmp al, 20h

        je word_end

        dec r9

        jmp prnt

        word_end:

            mov r8, r9
            inc r8
            call print_string
            dec r9
            jmp prnt
    
    end:
        
        mov r8, r9
        inc r8
        call print_string

        mov rax, 4
        mov rbx, 1
        mov rcx, nl
        mov rdx, 1
        int 80h

        mov rax, 1
        mov rbx, 0
        int 80h

scan_string:

    read_s:

        mov rax, 3
        mov rbx, 0
        mov rcx, c
        mov rdx, 1
        int 80h

        cmp byte[c], 10
        je end_s

        inc byte[strlen]
        mov al, byte[c]
        mov byte[r8], al
        inc r8

        jmp read_s

    end_s:

        mov byte[r8], 0
        ret 

    print_string:

    print_s:

        mov al, byte[r8]
        mov byte[c], al

        cmp byte[c], 0
        je end_p
        cmp byte[c], 20h
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
        mov rcx, space
        mov rdx, 1
        int 80h   

     ret 