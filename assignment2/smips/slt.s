main:

    li   $t1, 1
    move $a0, $t1         # printf("%d", 1);
    li   $v0, 1
    syscall

    li   $a0, '\n'      # printf("%c", '\n');
    li   $v0, 11
    syscall

    li   $t0, -3
    slt  $t1, $t0, $t3
    
    move $a0, $t0         
    li   $v0, 1
    syscall
    
    li   $a0, '\n'      # printf("%c", '\n');
    li   $v0, 11
    syscall

    jr   $ra
