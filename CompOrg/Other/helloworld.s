		.data
str: 	.asciiz "Hello World"
nl:     .asciiz "\n"

		.text
main:	
		li $v0, 4
		la $a0, str
		syscall

		li $v0, 4
		la $a0, nl
		syscall


		li $v0, 1
		li $a0, 102
		syscall 

		li $v0, 4
		la $a0, nl
		syscall


		li $t0, 24
		li $t1, 12

		add $a0 $t0, $t1
		li $v0, 1
		syscall

		mult $t0, $t1
		mflo $a0

		syscall

		beq $t0, $t1, here

		li $v0, 4
		la $a0, str
		syscall

		j 		here_end

here: 
		li $v0, 1
		la $a0, 1001
		syscall


here_end:

		li $v0, 1
		la $a0, 0110
		syscall


		li $v0, 10
		syscall