.data

    msg1: .asciiz "Enter the string: "
    msg2: .asciiz "Largest word: "
    msg3: .asciiz "Smallest word: "
    smallest: .space 25
    largest: .space 25
    str: .space 100

.text

.globl main

main:

    li $v0, 4
    la $a0, msg1
    syscall

    la $a0, str
    li $a1, 100
    li $v0, 8
    syscall

    li $t0, 105
    li $t1, -1
    la $t5, str
    addi $t5, $t5, -1
    la $s0, str
    la $s1, str
    li $s5, 10

    loop:
        li $t2, 0
        addi $t5, $t5, 1
        move $s2, $t5
        scan_word:

            lb $t3, 0($t5)
            beq $t3, 32, wordEnd
            beq $t3, 10, wordEnd

            addi $t5, $t5, 1
            addi $t2, $t2, 1
            j scan_word

        wordEnd:

            blt $t2, $t0, smaller
            cnt1:
            bgt $t2, $t1, larger
            cnt2:
            beq $t3, 10, end
            j loop

    smaller:
        move $s0, $s2
        move $t0, $t2
        j cnt1
    
    larger:
        move $s1, $s2
        move $t1, $t2
        j cnt2
       

    end:
        la $t2, smallest
        copy_small:

            lb $t3, 0($s0)
            beq $t3, 10, endSmall
            beq $t3, 32, endSmall

            sb $t3, 0($t2)
            addi $s0, $s0, 1
            addi $t2, $t2, 1

            j copy_small

        endSmall:

            sb $s5, 0($t2)
            sb $zero, 1($t2)

        la $t2, largest

        copy_large:

            lb $t3, 0($s1)
            beq $t3, 10, endLarge
            beq $t3, 32, endLarge

            sb $t3, 0($t2)
            addi $s1, $s1, 1
            addi $t2, $t2, 1

            j copy_large

        endLarge:

            sb $s5, 0($t2)
            sb $zero, 1($t2)
        
        li $v0, 4
        la $a0, msg3
        syscall

        li $v0, 4
        la $a0, smallest
        syscall

        li $v0, 4
        la $a0, msg2
        syscall

        li $v0, 4
        la $a0, largest
        syscall

        li $v0, 10
        syscall

        
            







