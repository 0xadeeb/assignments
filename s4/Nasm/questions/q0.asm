section .data

    msg1: db "Enter the string : "
    size1: equ $-msg1

    msg2: db "Balanced string : "
    size2: equ $-msg2

    space: db 20h

    nl: db 10

section .bss

string: resb 100
count: resb 1
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

    mov byte[count], 0

    mov byte[strlen], 0
    mov r8, string
    call scan_string

    mov r8, string

    mov rax, 4
    mov rbx, 1
    mov rcx, msg2
    mov rdx, size2
    int 80h

    print:
        mov al, byte[r8]
        mov byte[c], al

        cmp byte[c], 0
        je end_p

        cmp byte[c], 28h
        je incCount
        cmp byte[c], 29h
        je decCount
        
        mov rax, 4
        mov rbx, 1
        mov rcx, c 
        mov rdx, 1
        int 80h

        inc r8
        jmp print

        incCount:
            
            mov rax, 4
            mov rbx, 1
            mov rcx, c 
            mov rdx, 1
            int 80h

            inc r8
            inc byte[count]
            jmp print

        decCount:

            cmp byte[count], 0
            je rePrint
            
            mov rax, 4
            mov rbx, 1
            mov rcx, c 
            mov rdx, 1
            int 80h

            inc r8
            dec byte[count]
            jmp print

            rePrint:
                inc r8
                jmp print

    end_p:

        mov byte[c], 29h
        Pbracket:

            cmp byte[count], 0
            je end

            mov rax, 4
            mov rbx, 1
            mov rcx, c 
            mov rdx, 1
            int 80h

            dec byte[count]
            jmp Pbracket

        end:
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





