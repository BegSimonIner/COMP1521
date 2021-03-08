# Weekly Test 7 COMP1521
# Written by Rifa Jamal - z5311190
# Written on 23/07/2020

# read a line and print whether it is a palindrom

# int i in $s0

main:
    la   $a0, str0       # printf("Enter a line of input: ");
    li   $v0, 4
    syscall

    la   $a0, line
    la   $a1, 256
    li   $v0, 8             # fgets(buffer, 256, stdin)
    syscall                 


    li   $s0, 0             # int i = 0;

loop1:

    la $t0, line
    add $t1, $s0, $t0
    lb $t2, ($t1)

    beq	$t2, 0, loop1_end	# if line[i] == 0 then loop_end
    
    addi $s0, $s0, 1	    # i++;
    b loop1

loop1_end:

    li   $s1, 0             # int j = 0;
    addi $s2, $s0, -2       # int k = i - 2;

loop2:

    bge	$s1, $s2, loop2_end	# if j >= k then loop2_end
    
    la $t0, line
    add $t1, $s1, $t0
    lb $t2, ($t1)           # $t2 = line[j]

    la $t0, line
    add $t1, $s2, $t0
    lb $t3, ($t1)           # $t2 = line[k]

    beq	$t2, $t3, loop2_increment  # if j == k then target
    
    la   $a0, not_palindrome
    li   $v0, 4
    syscall

    li   $v0, 0          # return 0
    jr   $31

loop2_increment:

    addi $s1, $s1, 1	# j++;
    addi $s2, $s2, -1    # k++;
    b loop2
    
loop2_end:

    la   $a0, palindrome
    li   $v0, 4
    syscall

    li   $v0, 0          # return 0
    jr   $31


.data
str0:
    .asciiz "Enter a line of input: "
palindrome:
    .asciiz "palindrome\n"
not_palindrome:
    .asciiz "not palindrome\n"


# line of input stored here
line:
    .space 256

