	    .data
even:    .word 2, 4, 6, 8
odd:     .word 1, 3, 5, 7
len:     .word 4
 


		.text

main:   la $s0, even
		la $s1, odd

		li $t0, 0       #counter
		la $t1, len     #length

sav:    beq $t0, $t1, end
		sll $t2, $t0, 2     #t2 = i
		add $t3, $s0, $t2   #t3 index of arr1
		add $t4, $s1, $t2   #t4 index of arr2
		lw $t5, 0($t3)
		lw $t6, 0($t4)
		sw $t6, 0($t3)
		sw $t5, 0($t4)
		addi $t0, $t0, 1
		j sav





end: 

	li $v0, 10
	syscall


	

