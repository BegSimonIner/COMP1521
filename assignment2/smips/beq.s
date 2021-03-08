main:

    li   $t1, 1
    move $a0, $t1         # printf("%d", 1);
    li   $v0, 1
    syscall

    li   $a0, '\n'      # printf("%c", '\n');
    li   $v0, 11
    syscall

bne1:

    li  $t0, 1
    beq	$t1, $t0, main	# if  != $t1 then target


    jr   $ra
