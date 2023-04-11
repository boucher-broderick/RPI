

		.data
e:   .asciiz "EVEN\n"
o:   .asciiz "ODD\n"
list: .word 12, 100, -101, 5, 0, 123456789, 18


		.text


isodd: 	
		li $t0, 2
		div $s1, $t0
		mfhi $t1
		

		bgt $t1, $zero, if
		li $v0, 0
		jr 	 $ra

if: 	li $v0, 4
		move $t1, $a0
		la $a0, o
		syscall
		move $a0, $t1
		li $v0, 1
		jr  $ra

numodds: 

		
		
		li $t8, 0
		
		
loop:	blt $t8, $a1, end
	
		addi $a0, $a0, 4
		lw $t0, 0($a0)
		move $s1, $t0
		jal isodd

		add $v1 $v1, $v0
		
		addi $t8, $t8, 1
		jr loop
		


end: 
	jr $ra



		
main: 	

		li $v1, 0
		li $a1, 7
		la $a0, list
		jal numodds


		move $a0, $v1
		li $v0, 1
		syscall

	
		li $v0, 10
		syscall

