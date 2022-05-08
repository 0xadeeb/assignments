section .data

    msg1: db "Enter the string : "
    size1: equ $-msg1

    msg2: db "Enter to word to be found and replaced: "
    size2: equ $-msg2

    msg3: db "Enter the word to replace: "
    size3: equ $-msg3

    space: db 20h

    nl: db 10
    sp_count: db 0
    pos: db 0

section .bss

    digit: resw 1
    dgt: resb 1
    string1: resb 100
    string2: resb 100
    word1: resb 15
    word1_l: resq 1
    word2: resb 15
    c: resb 1
    strlen: resb 1
    count: resb 1

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
    mov byte[r8], 20h
    inc r8
    call scan_string

    mov rax, 4
    mov rbx, 1
    mov rcx, msg2
    mov rdx, size2
    int 80h

    mov r8, word1
    mov byte[r8], 20h
    inc r8
    mov byte[strlen], 0
    call scan_string

    mov r8, 0
    mov r8b, byte[strlen]
    add r8, 2
    mov qword[word1_l], r8

    mov rax, 4
    mov rbx, 1
    mov rcx, msg3
    mov rdx, size3
    int 80h

    mov r8, word2
    mov byte[r8], 20h
    inc r8
    call scan_string

    mov r8, string1
    mov r9, word1
    mov r12, string2
    mov r10, word2
    mov r11, r8

    call find_and_replace

    mov r8, string2
    inc r8
    call print_string

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

        mov byte[r8], 20h
        inc r8
        mov byte[r8], 0
        ret 

find_and_replace:

    check:
        mov byte[sp_count], 0
        cmp byte[r11], 0
        je exit_fnr

        cmp byte[r9], 0
        je sim

        mov r14b, byte[r9]

        cmp r14b, byte[r11]
        jne not_sim

        inc r11
        inc r9
        jmp check

        not_sim:

            mov r11, r8
            cmp byte[r8], 20h
            je not_sim_end
            cnt:
            cmp byte[r8], 0
            je check

            mov r14b, byte[r8]
            mov byte[r12], r14b

            inc r12
            inc r8
            jmp not_sim

            not_sim_end:
                mov r9, word1
                inc byte[sp_count]
                cmp byte[sp_count], 2
                jne cnt
                jmp check

        sim:
            
            cmp byte[r10], 0
            je end_copy

            mov r14b, byte[r10]
            mov byte[r12], r14b

            inc r10
            inc r12
            jmp sim

            end_copy:
                mov r9, word1
                mov r10, word2
                add r8, qword[word1_l]
                jmp check
    exit_fnr:
        mov byte[r12], 0
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