.data

    str: .asciiz "Enter the number: "
    space: .asciiz " " 


.globl main
.text
main:

    li $t1, 0
    li $t2, 1

    li $v0, 4
    la $a0, str
    syscall

    li $v0, 5
    syscall

    move $t5, $v0

    loop:
        beq $t5, $zero, end

        li $v0, 1
        move $a0, $t1
        syscall

        li $v0, 4
        la $a0, space
        syscall

        move $t3, $t1
        move $t1, $t2
        add $t2, $t1, $t3

        addi $t5, -1
        j loop
    
    end:

        li $v0, 10
        syscall


