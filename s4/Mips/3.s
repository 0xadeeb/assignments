.data

    msg1: .asciiz "Enter the first string: "
    msg2: .asciiz "Enter the second string: "
    msg3: .asciiz "Concatinated string: "
    str1: .space 50
    str2: .space 50
    str: .space 100

.text

.globl main

main:

    li $v0, 4
    la $a0, msg1
    syscall

    la $a0, str1
    li $a1, 50
    li $v0, 8
    syscall

    li $v0, 4
    la $a0, msg2
    syscall

    la $a0, str2
    li $a1, 50
    li $v0, 8
    syscall

    la $t0, str
    la $t1, str1
    la $t2, str2
    li $s5, 10

    copyStr1:

        lb $t5, 0($t1)
        beq $t5, 10, copyStr2
        sb $t5, 0($t0)

        addi $t0, $t0, 1
        addi $t1, $t1, 1
        j copyStr1
    
    copyStr2:

        lb $t5, 0($t2)
        beq $t5, $zero, end
        sb $t5, 0($t0)

        addi $t0, $t0, 1
        addi $t2, $t2, 1
        j copyStr2

    end:
        sb $zero, 0($t0)

        li $v0, 4
        la $a0, str
        syscall

        li $v0, 10
        syscall
        



