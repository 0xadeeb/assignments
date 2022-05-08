section .bss
digit0: resb 10
digit1: resb 10
array: resb 50 
junk: resb 10
n: resw 10
no_odd: resb 10
temp: resw 10
no_even: resb 10
ans1 : resb 10
ans2 : resb 10

section .data
msg1: db "Enter the number of elements : "
size1: equ $-msg1
msg2: db "Enter element i :"
size2: equ $-msg2
msg3: db "Number of odd elements in the array  ",
size3: equ $-msg3
msg4: db "Number of even elements in the array- "
size4: equ $-msg4
n1: db 10
l: equ $n1

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

mov [temp], ax
mov rbx, array

reading:

push rbx
push rcx
push rdx

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
mov rdx, 2
int 80h
sub byte[digit1], 30h
sub byte[digit0], 30h
mov al, byte[digit1]
mov dl, 10
mul dl
add al, byte[digit0]

pop rdx
pop rcx
pop rbx
mov byte[rbx], al
add rbx, 1

dec word[temp]
cmp word[temp], 0
jg reading



mov rbx, array
mov byte[no_even], 0
mov byte[no_odd], 0


searching:

    push rbx
    mov ax , word[rbx]
    mov ah, 0
    mov bl, 2
    div bl

    cmp ah, 0
    je even
    add byte[no_odd], 1
    jmp next

    even:
        add byte[no_even], 1
    
    next:
        pop rbx
        dec byte[n]
        add rbx, 1
        cmp byte[n],0
        jg searching



    
add byte[no_odd], 30h
add byte[no_even], 30h

mov rax, 4
mov rbx, 1
mov rcx, msg3
mov rdx, size3
int 80h
    
mov rax, 4
mov rbx, 1
mov rcx, no_odd
mov rdx, 1
int 80h
        
mov rax, 4
mov rbx, 1
mov rcx, n1
mov rdx, 1
int 80h

mov rax, 4
mov rbx, 1
mov rcx, msg4
mov rdx, size4
int 80h
    
mov rax, 4
mov rbx, 1
mov rcx, no_even
mov rdx, 1
int 80h

        
mov rax, 4
mov rbx, 1
mov rcx, n1
mov rdx, 1
int 80h

mov rax, 1
mov rbx, 0
int 80h



