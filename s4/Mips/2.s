.data

    msg1: .asciiz "Enter the first number: "
    msg2: .asciiz "Enter the second number: "
    prime: .asciiz "The pair is a twin prime.\n"
    Notprime: .asciiz "The pair not is a twin prime.\n"
    space: .asciiz " " 

.text

.globl main

main:

    li $v0, 4
    la $a0, msg1
    syscall

    li $v0, 5
    syscall

    move $s0, $v0

    li $v0, 4
    la $a0, msg2
    syscall

    li $v0, 5
    syscall

    move $s1, $v0

    sub $t0, $s1, $s0

    li $t1, -2
    li $t2, 2

    beq $t0, $t1, first_condPass
    beq $t0, $t2, first_condPass

    j not_P

    first_condPass:
        addi $t0, $s0, -1
        addi $t1, $s1, -1
        addi $t2, $t2, -1
        
        check_1stNo:
            beq $t0, $t2, check_2ndNo

            rem $t3, $s0, $t0

            beq $t3, $zero, not_P

            addi $t0, $t0, -1
            j check_1stNo
        
        check_2ndNo:
            beq $t1, $t2, is_p

            rem $t3, $s1, $t1

            beq $t3, $zero, not_P

            addi $t1, $t1, -1
            j check_2ndNo

    not_P:
        li $v0, 4
        la $a0, Notprime
        syscall

        j end

    is_p:
        li $v0, 4
        la $a0, prime
        syscall

    end:

        li $v0, 10
        syscall
        

