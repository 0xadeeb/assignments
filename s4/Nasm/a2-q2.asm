section .data

msg1: db "Enter the number of elements : "
size1: equ $-msg1

msg2: db "Enter element i : "
size2: equ $-msg2

msg3: db "The elemnts divisible by 7 are :", 10
size3: equ $-msg3

nl: db 10

section .bss

digit0: resb 1
digit1: resb 1
array: resb 50 
junk: resb 1
n: resw 1
element: resb 1
temp: resb 1

section .text

global _start
_start:

    mov rax, 4
    mov rbx, 1
    mov rcx, msg1
    mov rdx, size1
    int 80h

    mov rax, 3
    mov rbx, 0
    mov rcx, digit1
    mov rdx, 1
    int 80h

    mov rax, 3
    mov rbx, 0
    mov rcx, digit0
    mov rdx, 1
    int 80h

    mov rax, 3
    mov rbx, 0
    mov rcx, junk
    mov rdx, 1
    int 80h


    sub byte[digit1], 30h
    sub byte[digit0], 30h
    mov al, byte[digit1]
    mov dl, 10
    mul dl
    mov bx, word[digit0]
    add ax, bx
    mov [n], ax

    mov [temp], al
    mov rbx, array

    read:
        push rbx

        mov rax, 4
        mov rbx, 1
        mov rcx, msg2
        mov rdx, size2
        int 80h

        mov rax, 3
        mov rbx, 0
        mov rcx, digit1
        mov rdx, 1
        int 80h

        mov rax, 3
        mov rbx, 0
        mov rcx, digit0
        mov rdx, 1
        int 80h
        
        mov rax, 3
        mov rbx, 0
        mov rcx, junk
        mov rdx, 1
        int 80h

        sub byte[digit1], 30h
        sub byte[digit0], 30h
        mov al, byte[digit1]
        mov dl, 10
        mul dl
        mov bx, word[digit0]
        add ax, bx

        pop rbx
        mov word[rbx], ax

        inc rbx
        dec byte[temp]

        cmp byte[temp], 0
        jne read

    mov rax, 4
    mov rbx, 1
    mov rcx, msg3
    mov rdx, size3
    int 80h

    mov al, byte[n]
    mov [temp], al
    mov rbx, array

    check:
        mov ax, word[rbx]
        mov ah, 0
        mov cl, 7
        div cl

        cmp ah, 0
        jne next 

        mov ax, word[rbx]
        mov ah, 0
        mov cl, 10
        div cl

        mov byte[digit1], al
        mov byte[digit0], ah

        add byte[digit1], 30h
        add byte[digit0], 30h

        push rbx

        mov rax, 4
        mov rbx, 1
        mov rcx, digit1
        mov rdx, 1
        int 80h

        mov rax, 4
        mov rbx, 1
        mov rcx, digit0
        mov rdx, 1
        int 80h

        mov rax, 4
        mov rbx, 1
        mov rcx, nl
        mov rdx, 1
        int 80h

        pop rbx
        next:
            inc rbx
            dec byte[temp]

            cmp byte[temp], 0
            jne check
    
    mov rax, 1
    mov rbx, 0
    int 80h