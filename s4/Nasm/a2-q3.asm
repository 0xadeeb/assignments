section .data

msg1: db "Enter the number of elements : "
size1: equ $-msg1

msg2: db "Enter element i : "
size2: equ $-msg2

msg3: db "The sum of the entire array: "
size3: equ $-msg3

msg4: db "Average of the elements in the array: "
size4: equ $-msg4

nl: db 10

section .bss

digit: resw 1
dgt: resb 1
count: resb 1
array: resw 100
n: resw 1
temp: resw 1
sum: resw 1
avg: resw 1

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
    mov word[n], ax
    mov word[temp], ax
    mov rbx, array

    scan_array:

        push rbx

        mov rax, 4
        mov rbx, 1
        mov rcx, msg2
        mov rdx, size2
        int 80h

        call scan_digit

        pop rbx
        mov ax, word[digit]
        mov word[rbx], ax

        add rbx, 2
        dec word[temp]

        cmp word[temp], 0
        
        jne scan_array

    mov ax, word[n]
    mov word[temp], ax
    mov rbx, array

    mov cx, 0

    find_sum:

        add cx, word[rbx]
        add rbx, 2
        dec word[temp]

        cmp word[temp], 0
        jne find_sum
    
    mov word[sum],cx

    mov rax, 4
    mov rbx, 1
    mov rcx, msg3
    mov rdx, size3
    int 80h

    mov ax, word[sum]
    mov word[digit], ax
    call print_digit

    mov ax, word[sum]
    mov dx, 0
    mov bx, word[n]

    div bx
    mov word[avg], ax

    mov rax, 4
    mov rbx, 1
    mov rcx, msg4
    mov rdx, size4
    int 80h

    mov al, byte[avg]
    mov ah, 0
    mov word[digit], ax

    call print_digit

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








