







       .data
star:   .asciiz "*"
newline:     .asciiz "\n"

       .text
print_triangle:
  move $t0, $a0        # loop counter for rows
  sll  $t1, $a0, 1     # max length = 2n - 1
  sub  $t1, $t1, 1

loop:
  beq  $t0, $zero, exit

  li   $v0, 4          # setup up syscall to print stars
  la   $a0, star       # setup up syscall to print stars
  move $t4, $t1        # loop counter for stars
print_stars:
  beq  $t4, $zero, done_stars

  syscall              # print a star

  add  $t4, $t4, -1
  j print_stars

done_stars:

  la   $a0, newline     # print newline
  syscall
  
  add  $t0, $t0, -1
  addi $t1, $t1, -2
  j loop

exit:
  jr   $ra

main:
       li $a0, 4
       jal print_triangle

       li $v0, 10
       syscall