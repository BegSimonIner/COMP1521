# Weekly Test 7 COMP1521
# Written by Rifa Jamal - z5311190
# Written on 23/07/2020

# read a line and print its length

main:
    la   $a0, str0          # printf("Enter a line of input: ");
    li   $v0, 4
    syscall

    la   $a0, line
    la   $a1, 256
    li   $v0, 8             # fgets(buffer, 256, stdin)
    syscall                 #

    li   $t0, 0             # int i = 0;

loop_start:

    la $t1, line
    add $t2, $t0, $t1
    lb $t3, ($t2)

    beq	$t3, 0, loop_end	# if line[i] == 0 then loop_end
    
    addi $t0, $t0, 1	    # i++;
    b loop_start

loop_end:

    la   $a0, str1          # printf("Line length: ");
    li   $v0, 4
    syscall

    move $a0, $t0           # printf("%d", i);
    li   $v0, 1
    syscall

    li   $a0, '\n'          # printf("%c", '\n');
    li   $v0, 11
    syscall

    li   $v0, 0          # return 0
    jr   $31


.data
str0:
    .asciiz "Enter a line of input: "
str1:
    .asciiz "Line length: "


# line of input stored here
line:
    .space 256

