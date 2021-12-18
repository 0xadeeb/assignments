.data

    msg1: .asciiz "Enter the string: "
    msg2: .asciiz "Enter the word to be replaced: "
    msg3: .asciiz "Enter the alternative word: "
    space: .asciiz " "
    string: .space 100
    array: .word 0 : 25
    word1: .space 25
    word2: .space 25

.text

.globl main

main:   

    la $t7, array
    la $t8, word1
    la $t9, word2
    la $s6, string

    li $v0, 4
    la $a0, msg1
    syscall

    la $a0, string
    li $a1, 100
    li $v0, 8
    syscall

    li $v0, 4
    la $a0, msg2
    syscall

    la $a0, word1
    li $a1, 25
    li $v0, 8
    syscall

    li $v0, 4
    la $a0, msg3
    syscall

    la $a0, word2
    li $a1, 25
    li $v0, 8
    syscall

    la $s2, word1
    la $s3, word2

    loop1:
        lb $t0, 0($s2)
        beq $t0, 10, loop2
        addi $s2, $s2, 1
        j loop1

    loop2:
        lb $t0, 0($s3)
        beq $t0, 10, endLoop
        addi $s3, $s3, 1
        j loop2

    endLoop:
        
        sb $zero, 0($s2)
        sb $zero, 0($s3)

    la $s0, string
    la $s1, array
    sw $s0, 0($s1)
    addi $s0, $s0, 1
    addi $s1, $s1, 4

    storeAdr:

        lb $t0, 0($s0)
        beq $t0, $zero, endAdr
        beq $t0, 32, wordEnd
        beq $t0, 10, wordEnd

        addi $s0, $s0, 1
        j storeAdr

        wordEnd:
            sb $zero, 0($s0)
            addi $s0, $s0, 1
            lb $t0, 0($s0)
            beq $t0, $zero, endAdr
            sw $s0, 0($s1)
            addi $s1, $s1, 4
            j storeAdr
    
    endAdr:
    
        li $t0, -1
        sw $t0, 0($s1)
        la $s1, array
        li $s5, -1


    check:
        lw $t0, 0($s1) 
        la $s2, word1
        la $s3, word2
        beq $t0, $s5, endCheck
        check_word:

            lb $t5, 0($t0)
            lb $t6, 0($s2)
            bne $t5, $t6, endWordcheck

            beq $t5, 0, simlar

            addi $t0, $t0, 1
            addi $s2, $s2, 1
            j check_word

        simlar:

            sw $s3, 0($s1)
            addi $s1, $s1, 4
            j check

        endWordcheck:

            addi $s1, $s1, 4
            j check

    endCheck:

    la $s1, array

    print:
        lw $a0, 0($s1)
        beq $a0, $s5, end

        li $v0, 4
        syscall

        la $a0, space
        syscall

        addi $s1, $s1, 4
        j print

    end:

    li $t0, 10

    la $a0, space
    sb $t0, 0($a0)
    syscall

    li $v0, 10
    syscall


            

        







            



    