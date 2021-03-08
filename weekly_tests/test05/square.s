# Weekly Test 5 COMP1521
# Written by Rifa Jamal - z5311190

main:
    li $v0, 5           #   scanf("%d", &x);
    syscall             #
    move $t0, $v0


    li $t1, 0                   # int i = 0  
    
loop1:

    bge	$t1, $t0, main_end	    # if x >= i then target
    li $t2, 0                   # int j = 0 

loop2:
    bge	$t2, $t0, loop1_increment	    # if x >= j then target
    
    li   $a0, '*'              # printf("%c", '*');
    li   $v0, 11
    syscall

loop2_increment:

    addi	$t2, $t2, 1			# j = j + 1
    j loop2

loop1_increment:

    addi	$t1, $t1, 1			# i = 1 + 1;
    
    li   $a0, '\n'              # printf("%c", '\n');
    li   $v0, 11
    syscall

    j loop1

main_end:

    li $v0, 0           # return 0
    jr $31
