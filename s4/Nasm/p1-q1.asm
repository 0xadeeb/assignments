section .data

msg1 : db 'Enter first digit of first number :'
l1 : equ $-msg1
msg2 : db 'Enter second digit of first number :'
l2 : equ $-msg2
msg3 : db 'Enter first digit of second number :'
l3 : equ $-msg3
msg4 : db 'Enter second digit of second number :'
l4 : equ $-msg4
msg5 : db 'Enter first digit of third number :'
l5 : equ $-msg5
msg6 : db 'Enter second digit of third number :'
l6 : equ $-msg6
nwl : db ' ', 10
new_l : equ $-nwl

section .bss

d1 : resb 1
d2 : resw 1
d3 : resb 1
d4 : resw 1
d5 : resb 1
d6 : resw 1
n1 : resb 1
n2 : resb 1
n3 : resb 1

ans1 : resb 1
ans2 : resb 1
ans3 : resb 1
ans4 : resw 1
junk : resb 1
junk1 : resb 1
junk2 : resb 1

section .text

	global _start:
	_start:
	mov eax, 4
	mov ebx, 1
	mov ecx, msg1
	mov edx, l1
	int 80h

	mov eax, 3
	mov ebx, 0
	mov ecx, d1
	mov edx, 1
	int 80h

	mov eax, 3
	mov ebx, 0
	mov ecx, junk
	mov edx, 1
	int 80h

	mov eax, 4
	mov ebx, 1
	mov ecx, msg2
	mov edx, l2
	int 80h

	mov eax, 3
	mov ebx, 0
	mov ecx, d2
	mov edx, 1
	int 80h

	mov eax, 3
	mov ebx, 0
	mov ecx, junk1
	mov edx, 1
	int 80h
	
	mov al, byte[d1]
	sub al, 30h
	mov bl, 10
	mov ah, 0
	mul bl
	mov bx, word[d2]
	sub bx, 30h
	add ax, bx
	mov [n1], ax

	
	mov eax, 4
	mov ebx, 1
	mov ecx, msg3
	mov edx, l3
	int 80h

	mov eax, 3
	mov ebx, 0
	mov ecx, d3
	mov edx, 1
	int 80h

	mov eax, 3
	mov ebx, 0
	mov ecx, junk2
	mov edx, 1
	int 80h

	mov eax, 4
	mov ebx, 1
	mov ecx, msg4
	mov edx, l4
	int 80h

	mov eax, 3
	mov ebx, 0
	mov ecx, d4
	mov edx, 1
	int 80h
	
	mov eax, 3
	mov ebx, 0
	mov ecx, junk2
	mov edx, 1
	int 80h	
	
	mov al, byte[d3]
	sub al, 30h
	mov bl, 10
	mov ah, 0
	mul bl
	mov bx, word[d4]
	sub bx, 30h
	add ax, bx
	mov [n2], ax
	
	mov eax, 4
	mov ebx, 1
	mov ecx, msg5
	mov edx, l5
	int 80h

	mov eax, 3
	mov ebx, 0
	mov ecx, d5
	mov edx, 1
	int 80h

	mov eax, 3
	mov ebx, 0
	mov ecx, junk2
	mov edx, 1
	int 80h

	mov eax, 4
	mov ebx, 1
	mov ecx, msg6
	mov edx, l6
	int 80h

	mov eax, 3
	mov ebx, 0
	mov ecx, d6
	mov edx, 1
	int 80h
	
	mov eax, 3
	mov ebx, 0
	mov ecx, junk2
	mov edx, 1
	int 80h	
	
	mov al, byte[d5]
	sub al, 30h
	mov bl, 10
	mov ah, 0
	mul bl
	mov bx, word[d6]
	sub bx, 30h
	add ax, bx
	mov [n3], ax
	
	mov al, byte[n1]
	cmp al, byte[n2]
	jl if


	cmp al, byte[n3]
	jl A

	mov al, byte[n3]
	cmp al, byte[n2]
	jl B 

	jmp C
	
	if:

		mov al, byte[n1]
		cmp al, byte[n3]
		jg A

		mov al, byte[n2]
		cmp al, byte[n3]
		jl B

		jmp C
	

	A:
	mov ax, word[n1]
	mov ah, 0
	mov bl, 10
	div bl
	
	mov [ans1], al
	mov [ans2], ah
	add byte[ans1], 30h
	add byte[ans2], 30h
	
	mov eax, 4
	mov ebx, 1
	mov ecx, ans1
	mov edx, 1
	int 80h
	
	mov eax, 4
	mov ebx, 1
	mov ecx, ans2
	mov edx, 1
	int 80h
	
	jmp END 

	B:
	mov ax, word[n2]
	mov ah, 0
	mov bl, 10
	div bl

	mov [ans1], al
	mov [ans2], ah
	add byte[ans1], 30h
	add byte[ans2], 30h	
	
	mov eax, 4
	mov ebx, 1
	mov ecx, ans1
	mov edx, 1
	int 80h
	
	mov eax, 4
	mov ebx, 1
	mov ecx, ans2
	mov edx, 1
	int 80h
	
	jmp END

	C:

	mov ax, word[n3]
	mov ah, 0
	mov bl, 10
	div bl
	
	mov [ans1], al
	mov [ans2], ah
	add byte[ans1], 30h
	add byte[ans2], 30h	
	
	mov eax, 4
	mov ebx, 1
	mov ecx, ans1
	mov edx, 1
	int 80h
	
	mov eax, 4
	mov ebx, 1
	mov ecx, ans2
	mov edx, 1
	int 80h
	
	jmp END
		


	END:
		mov eax, 4
		mov ebx, 1
		mov ecx, nwl
		mov edx, new_l
		int 80h
			
		mov eax, 1
		mov ebx, 0
		int 80h
			
	

        ; mov rax, 4
        ; mov rbx, 1
        ; mov rcx, msgr
        ; mov rdx, sr
        ; int 80h
        ;     mov word[digit], r12w
        ;     call print_digit
        ;     mov rax, 4
        ; mov rbx, 1
        ; mov rcx, msga
        ; mov rdx, sa
        ; int 80h
        ;     mov word[digit], r9w
        ; call print_digit
        ; mov rax, 4
        ; mov rbx, 1
        ; mov rcx, msgb
        ; mov rdx, sb
        ; int 80h
        ; mov word[digit], r10w
        ; call print_digit