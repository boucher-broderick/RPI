

		.data
e:   .asciiz "EVEN\n"
o:   .asciiz "ODD\n"


		.text


isodd: 	
		sra $t1,$s0,31   
		xor $s0,$s0,$t1   
		sub $s0,$s0,$t1 
		li $t0, 2
		div $s0, $t0
		mfhi $t1
		

		bgt $t1, $zero, if
		li $v0, 0
		jr 	 $ra

if: 	li $v0, 1
		jr  $ra


		
main: 
		li $s0, -5
		jal   isodd

		move $t1, $v0

		beq $t1, $zero, even
		li $v0, 4
		la $a0, o
		syscall

		jr cont
		
even: 

		li $v0, 4
		la $a0, e
		syscall

cont:		
		li $v0, 10
		syscall

