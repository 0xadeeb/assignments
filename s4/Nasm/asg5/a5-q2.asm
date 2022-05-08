section .data

    msg1: db "Enter the string : "
    size1: equ $-msg1

    msg2: db "Number of repeating sequences: "
    size2: equ $-msg2

    msga: db "A: "
    sa: equ $-msga

    msgb: db "B: "
    sb: equ $-msgb

    msgr: db "Ret: "
    sr: equ $-msgr

    space: db 20h

    nl: db 10

section .bss

    digit: resw 1
    dgt: resb 1
    count: resb 1
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
    mov byte[r8],0
    inc r8
    call scan_string

    movzx r9,  byte[strlen]
    movzx r10, byte[strlen]

    mov r12, 0
    mov r8, string
    call lrs

    mov word[digit], r12w

    cmp r12, 0
    je print_0

    call print_digit

    mov rax, 1
    mov rbx, 0
    int 80h

    print_0:

        mov byte[c], 30h
        mov rax, 4
        mov rbx, 1
        mov rcx, c
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

lrs:

    cmp r9, 0
    je both_zero

    cmp r10, 0
    je both_zero

    mov r13, r8
    mov r14, r8
    add r13, r9
    add r14, r10
    mov cl, byte[r13]
    

    cmp cl, byte[r14]
    je if

    else:

        dec r9
        call lrs
        mov rax, r12
        inc r9

        dec r10
        call lrs
        mov rbx, r12
        inc r10

        cmp rax, rbx
        ja ret_a
        ret

        ret_a:
            mov r12, rax
            ret

    if:

        cmp r9, r10
        je else

        dec r9
        dec r10

        call lrs
        inc r9
        inc r10
        inc r12
        ret

    both_zero:

        mov r12, 0
        ret

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


print_digit:

    mov byte[count], 0

    extract_no:

        cmp word[digit] , 0
        je p_digit

        inc byte[count]
        mov ax, word[digit]
        mov rdx, 0
        mov bx, 10
        div bx

        push rdx

        mov word[digit], ax

        jmp extract_no

    p_digit:

        cmp byte[count], 0
        je end_print

        dec byte[count]
        pop rdx
        mov byte[dgt], dl
        add byte[dgt], 30h

        mov rax, 4
        mov rbx, 1
        mov rcx, dgt
        mov rdx, 1
        int 80h

        jmp p_digit

        end_print:

        mov rax, 4
        mov rbx, 1
        mov rcx, nl
        mov rdx, 1
        int 80h
        ret

    