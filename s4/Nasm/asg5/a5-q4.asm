section .data

    msg1: db "Enter the string : "
    size1: equ $-msg1

    msg2: db "Smallest word : "
    size2: equ $-msg2

    msg3: db "Largest word : "
    size3: equ $-msg3

    space: db 20h

    nl: db 10

    largest: db 0
    
    smallest: db 0xff

    len: dq 0

section .bss

    string: resb 100
    c: resb 1
    strlen: resb 1
    l: resq 1
    s: resq 1
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
    mov r8, string 
    call scan_string

    mov rax, 4
    mov rbx, 1
    mov rcx, msg2
    mov rdx, size2
    int 80h

    mov r8, 0
    mov r8 , qword[s]
    call print_string

    mov rax, 4
    mov rbx, 1
    mov rcx, msg3
    mov rdx, size3
    int 80h

    mov r8, 0
    mov r8, qword[l]
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
        je word_end_s

        cmp byte[c], 20h
        je word_end_s
        
        inc qword[len]
        cont:
        
        inc byte[strlen]
        mov al, byte[c]
        mov byte[r8], al
        inc r8

        jmp read_s

    word_end_s:

        mov r10, qword[len]

        cmp r10b, byte[largest]
        ja larger

        cont1:

        cmp r10b, byte[smallest]
        jb smaller  

        cont2:

        mov qword[len],0
        cmp byte[c],10
        je end_s

        jmp cont

    larger:

        mov r11, qword[len]
        mov byte[largest], r11b

        mov r11, r8
        sub r11, qword[len]
        mov qword[l], r11

        jmp cont1

    smaller:

        mov r11, qword[len]
        mov byte[smallest], r11b

        mov r11, r8
        sub r11, qword[len]
        mov qword[s], r11

        jmp cont2


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
        mov rcx, nl
        mov rdx, 1
        int 80h   

     ret 

