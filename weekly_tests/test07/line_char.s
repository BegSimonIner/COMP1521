# Weekly Test 7 COMP1521
# Written by Rifa Jamal - z5311190
# Written on 23/07/2020

#  read a line from stdin and and then an integer n
#  Print the character in the nth-position

# n in $t0

main:
    la   $a0, str0       # printf("Enter a line of input: ");
    li   $v0, 4
    syscall

    la   $a0, line       # fgets(buffer, 256, stdin)
    la   $a1, 256
    li   $v0, 8
    syscall

    la   $a0, str1       # printf("Enter a position: ");
    li   $v0, 4
    syscall

    li   $v0, 5          # scanf("%d");
    syscall
    move $t0, $v0

    la   $a0, str2       # printf("Character is: ");
    li   $v0, 4
    syscall

    la $t1, line         # find memory address of line
    add $t2, $t0, $t1    # add row position to line address to find row offset
    
    lb $a0, ($t2)	     # load address of line[n]
    li   $v0, 11         # printf("%c", '?');
    syscall

    li   $a0, '\n'       # printf("%c", '\n');
    li   $v0, 11
    syscall

    li   $v0, 0          # return 0
    jr   $31

.data
str0:
    .asciiz "Enter a line of input: "
str1:
    .asciiz "Enter a position: "
str2:
    .asciiz "Character is: "


# line of input stored here
line:
    .space 256

