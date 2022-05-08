section .data

    msg1: db "Enter the string : ",10
    size1: equ $-msg1

    space: db 20h

    nl: db 10

section .bss

string: resb 100
array: resq 25
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

    mov r8, string
    mov r9, array
    mov qword[r9], r8
    add r9, 8

    word_adr:

        cmp byte[r8], 20h
        je wordEnd

        inc r8
        jmp word_adr

        wordEnd:

            inc r8
            cmp byte[r8], 0
            je exit_adr
            mov qword[r9], r8
            add r9, 8
            jmp word_adr
    
    exit_adr:
        mov qword[r9], -1
    
    mov r8, array
    
        
    sort_array:

        cmp qword[r8+8], -1
        je exit_sort
        mov r9, array
        inner_loop:
            cmp qword[r9+8], -1
            je exit_innerLoop
            call compare
            cmp r10, 1
            je swap
            cnt:
            add r9,  8
            jmp inner_loop
        exit_innerLoop:

        add r8, 8
        jmp sort_array
        swap:

    mov r10, qword[r9]
    mov r11, qword[r9+8]

    mov qword[r9], r11
    mov qword[r9+8], r10
    jmp cnt

    exit_sort:

        mov r8, array
        ;add r8, 8
        print:

            cmp qword[r8], -1
            je exit 
            mov r9, qword[r8]
            call print_word
            add r8,  8
            jmp print
    exit:

    mov rax, 4
    mov rbx, 1
    mov rcx, nl
    mov rdx, 1
    int 80h

    mov rax, 1
    mov rbx, 0
    int 80h

compare:
    mov r13, qword[r9]
    mov r14, qword[r9+8]

    check:

        mov r11b, byte[r13]
        mov r12b, byte[r14] 

        cmp r11b, 20h
        je ret0
        cmp r12b, 20h
        je ret1

        cmp r11b, r12b
        jg ret1
        jl ret0

        inc r13
        inc r14
        jmp check

    ret0:
        mov r10, 0
        ret
    ret1:
        mov r10, 1
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

        mov byte[r8], 20h
        mov byte[r8+1], 0
        ret 

    print_word:

    print_s:

        mov al, byte[r9]
        mov byte[c], al

        cmp byte[c], 20h
        je end_p

        mov rax, 4
        mov rbx, 1
        mov rcx, c 
        mov rdx, 1
        int 80h

        inc r9

        jmp print_s

    end_p:

        mov rax, 4
        mov rbx, 1
        mov rcx, space
        mov rdx, 1
        int 80h   

     ret


    








