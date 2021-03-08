# Weekly Test 5 COMP1521
# Written by Rifa Jamal - z5311190

main:
    li $v0, 5           #   scanf("%d", &x);
    syscall             #
    move $t0, $v0

    li $v0, 5           #   scanf("%d", &y);
    syscall             #
    move $t1, $v0



    addi $t2, $t0, 1			# $t2 = $t0 + 1

loop_start:

    bge	$t2, $t1, main_end	    # if $t2 >= $t1 main_endtarget
    
    beq	$t2, 13, loop_increment	# if $t2 == 13 then target
    
    move $a0, $t2               # printf("%d", x); 
    li  $v0, 1
    syscall

    li   $a0, '\n'              # printf("%c", '\n');
    li   $v0, 11
    syscall


loop_increment:

    addi	$t2, $t2, 1			# i++;
    j loop_start
    

main_end:

    li $v0, 0           # return 0
    jr $31


