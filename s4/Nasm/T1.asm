section .data

    msg1: db "Enter the string : "
    size1: equ $-msg1

    msg2: db "Modified  string : "
    size2: equ $-msg2

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

    dec r8
    mov r9, r8
    mov r8, string

    cmp:

        cmp r9, r8
        jl end

        jmp check_alpha_dgt

        if1:
            inc r8
            jmp cmp
        
        if2:
            dec r9
            jmp cmp

        else:
            

            mov r10b, byte[r8]
            mov r11b, byte[r9]
            mov byte[r9], r10b
            mov byte[r8], r11b
            inc r8
            dec r9
            jmp cmp

        check_alpha_dgt:

            cmp byte[r8], 30h
            jl if1

            cmp byte[r8],65
            jl check_g_57_r8
            cnt1:

            cmp byte[r8], 97
            jl check_g_122_r8
            cnt2:

            cmp byte[r8], 122
            jg if1

            cmp byte[r9], 30h
            jl if2

            cmp byte[r9],65
            jl check_g_57_r9
            cnt3:

            cmp byte[r9], 97
            jl check_g_122_r9
            cnt4:

            cmp byte[r9], 122
            jg if2

            jmp else

            check_g_57_r8:
                cmp byte[r8], 57
                jg if1
                jmp cnt1

            check_g_122_r8:
                cmp byte[r8], 90
                jg if1
                jmp cnt2

            check_g_57_r9:
                cmp byte[r9], 57
                jg if2
                jmp cnt3

            check_g_122_r9:
                cmp byte[r9], 90
                jg if2
                jmp cnt4
    end:

        mov rax, 4
        mov rbx, 1
        mov rcx, msg2
        mov rdx, size2
        int 80h
        
        mov r8, string
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



