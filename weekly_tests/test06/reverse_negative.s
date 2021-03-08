# Week 6 Weekly Test COMP1521
# Written By Rifa Jamal (z5311190)

# Read numbers into an array until a negative number is entered
# then print the numbers in reverse order

# i in register $t0
# registers $t1, $t2 & $t3 used to hold temporary results

main:
    li $t0, 0           # i = 0
loop0:
    bge $t0, 1000, loop1 # while (i < 1000) {

    li $v0, 5           # scanf("%d", &x);
    syscall             #
    move $t1, $v0       # int x

if:
    bge	$t1, 0, else	# if $t1 >= 0 then target
    j loop1

else:
    mul $t2, $t0, 4     #   calculate &numbers[i]
    la $t3, numbers     #
    add $t4, $t2, $t3   #
    sw $t1, ($t4)       #   store entered number in array

    addi $t0, $t0, 1     #   i++;
    b loop0             # }


loop1:
    ble	$t0, 0, end	    # if i <= 0 then target
    addi $t0, $t0, -1   # i--;

    mul $t2, $t0, 4     # calculate &numbers[i]
    la $t3, numbers     #
    add $t4, $t2, $t3   #
    lw $a0, ($t4)       # load word stored in numbers[i]

    li $v0, 1           # printf("%d", numbers[i]);
    syscall

    li   $a0, '\n'      # printf("%c", '\n');
    li   $v0, 11
    syscall

    j loop1

end:

    li $v0, 0           # return 0
    jr $31              #

.data
numbers:
    .space 4000
