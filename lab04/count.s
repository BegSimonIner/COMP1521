# read a number n and print the integers 1..n one per line
# written by Rifa Jamal COMP1521 z5311190

main:                           # int main(void)

    # load counter
    li $t0, 1                   # i value
    li $t1, 0                   # kind of like initialing a name for the number enetered


                          
    la  $a0, prompt             # printf("Enter a number: ");
    li  $v0, 4
    syscall

    li  $v0, 5                  # scanf("%d", number);
    syscall
    move $t1, $v0

main__start:

    # while loop starts here
    # have a branch// see modified while loop in count.c

    bgt	$t0, $t1, main__end	    # if i > number then target
    
    move $a0, $t0               # move value you're printing (i) to a0
    # li  $a0,                  #printf("%d\n", i)
    li  $v0, 1
    syscall

    li   $a0, '\n'              # printf("%c", '\n');
    li   $v0, 11
    syscall

    #use add or add immediate to increment i
    addi	$t0, $t0, 1			# $t0 = $t0 + 1 (i = i + 1)
    
    # go back to start (of loop) using jump
    j main__start	# jump to target
    
main__end:

end:
    jr  $ra                     # return

    .data
prompt:
    .asciiz "Enter a number: "
