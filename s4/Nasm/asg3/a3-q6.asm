section .data

    msg1: db "Enter the string : "
    size1: equ $-msg1

    msg2: db "Number of vovels in the string: "
    size2: equ $-msg2

    nl: db 10

section .bss

    string: resb 100
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
    mov r8, string 
    call scan_string

    mov r8, string

    counting:
    
        mov al, byte[r8]
        
        cmp al, 0
        je endcounting
        
        cmp al, 65
        je next 
        
        cmp al, 69
        
        je next 
        
        cmp al, 73
        
        je next 
        
        cmp al, 79
        
        je next 
        
        cmp al, 85
        
        je next 
        
        cmp al, 97
        
        je next 
        
        cmp al, 101
        
        je next 
        
        cmp al, 105
        
        je next 
        
        cmp al, 111
        
        je next 
        
        cmp al, 117
        je next

        inc r8
        jmp counting
        
        
    next:
        inc byte[count]
        inc r8
        jmp counting
        
    endcounting:

        mov rax, 4
        mov rbx, 1
        mov rcx, msg2
        mov rdx, size2
        int 80h

        add byte[count], 30h

        mov rax, 4
        mov rbx, 1
        mov rcx, count
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







