section .data

msg1: db "Enter the number of elements array A : "
size1: equ $-msg1

msg2: db "Enter the number of elements array B : "
size2: equ $-msg2

msg3: db "Enter element ith of A : "
size3: equ $-msg3

msg4: db "Enter element ith of B : "
size4: equ $-msg4

msg5: db "Enter final array is : "
size5: equ $-msg5

nl: db 10

section .bss

digit: resw 1
dgt: resb 1
count: resb 1
arrayA: resw 100
arrayB: resw 100
arrayC: resw 100
n1: resw 1
n2: resw 1
n3: resw 1
b_start: resw 1
temp: resw 1
j: resw 1
i: resw 1

section .text

global _start
_start:

    mov rax, 4
    mov rbx, 1
    mov rcx, msg1
    mov rdx, size1
    int 80h

    call scan_digit
    mov ax, word[digit]
    inc ax
    mov word[n1], ax
    mov word[temp], ax
    mov rbx, arrayA


    scan_array1:

        push rbx

        mov rax, 4
        mov rbx, 1
        mov rcx, msg3
        mov rdx, size3
        int 80h

        call scan_digit

        pop rbx
        mov ax, word[digit]
        mov word[rbx], ax

        add rbx, 2
        dec word[temp]

        cmp word[temp], 1
        
        jne scan_array1
    
    mov word[rbx], 0xffff

    mov rax, 4
    mov rbx, 1
    mov rcx, msg2
    mov rdx, size2
    int 80h

    call scan_digit
    mov ax, word[digit]
    inc ax
    mov word[n2], ax
    mov word[temp], ax
    
    mov ax, word[n1]
    mov bx, word[n2]
    add ax, bx
    mov word[n3], ax

    mov rbx, arrayB
    mov word[rbx], 0xffff
    add rbx, 2

    scan_array2:

        push rbx

        mov rax, 4
        mov rbx, 1
        mov rcx, msg4
        mov rdx, size4
        int 80h

        call scan_digit

        pop rbx
        mov ax, word[digit]
        mov word[rbx], ax

        add rbx, 2
        dec word[temp]

        cmp word[temp], 1
        
        jne scan_array2

    
    sub rbx, 2
    mov ax, word[n3]
    mov word[temp], ax
    mov rcx, arrayC
    mov rax, arrayA
    sub word[temp], 2
    sub word[n3], 2
    

    merge:

        mov r8, [rax]
        mov r9, [rbx]
        cmp r8w, r9w

        jb copyA

        mov [rcx], r9
        dec word[temp]
        add rcx, 2
        sub rbx, 2
        cmp word[temp], 0
        je exit
        jmp merge       
        
        copyA:
            mov [rcx], r8
            dec word[temp]
            add rcx, 2
            add rax, 2
            cmp word[temp], 0
            jne merge

    exit:

    mov rax, 4
    mov rbx, 1
    mov rcx, msg5
    mov rdx, size5
    int 80h

    mov rax, 4
    mov rbx, 1
    mov rcx, nl
    mov rdx, 1
    int 80h

    mov rbx, arrayC
    mov ax, word[n3]
    mov word[temp], ax

    print_array:

        mov cx, word[rbx]
        mov word[digit], cx 

        push rbx
        call print_digit
        pop rbx
        
        dec word[temp]
        add rbx, 2

        cmp word[temp] , 0
        jne print_array

    
    mov rax, 1
    mov rbx, 0
    int 80h


scan_digit:

    mov word[digit], 0

    sc_lp:
        
        mov rax, 3
        mov rbx, 0
        mov rcx, dgt
        mov rdx, 1
        int 80h

        cmp byte[dgt], 10
        je end_lp

        sub byte[dgt], 30h
        mov ax, word[digit]
        mov bx, 10
        mul bx

        movzx bx, byte[dgt]
        add ax,bx

        mov word[digit], ax

        jmp sc_lp

    end_lp:
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



















