# Weekly Test 5 COMP1521
# Written by Rifa Jamal - z5311190

#  print the minimum of two integers
main:
    li $v0, 5           #   scanf("%d", &x);
    syscall             #
    move $t0, $v0

    li $v0, 5           #   scanf("%d", &y);
    syscall             #
    move $t1, $v0


    bge		$t0, $t1, print_y	# if x >= y then target

print_x:

    move $a0, $t0               # printf("%d", x); 
    li  $v0, 1
    syscall

    li   $a0, '\n'              # printf("%c", '\n');
    li   $v0, 11
    syscall

    j end

print_y:

    move $a0, $t1               # printf("%d", x); 
    li  $v0, 1
    syscall

    li   $a0, '\n'              # printf("%c", '\n');
    li   $v0, 11
    syscall


end:

    li $v0, 0           # return 0
    jr $31
    
