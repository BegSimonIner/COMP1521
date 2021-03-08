# COMP1521 Lab Rifa Jamal (z5311190)
# Written on 8/07/2020
# Week 5

# Read 10 numbers into an array
# print 0 if they are in non-decreasing order
# print 1 otherwise

# i in register $t0

main:

    li $t0, 0           # i = 0
loop0:
    bge $t0, 10, end0   # while (i < 10) {

    li $v0, 5           # scanf("%d", &numbers[i]);
    syscall             #

    mul $t1, $t0, 4     # calculate &numbers[i]
    la $t2, numbers     #
    add $t3, $t1, $t2   #
    sw $v0, ($t3)       # store entered number in array

    add $t0, $t0, 1     # i++;
    b loop0             # goto start of loop0
end0:

    li $t5, 0            # swapped = 0
    li $t0, 1            # i = 1

loop1:
    bge $t0, 10, end1    # while (i < 10) {

    mul $t1, $t0, 4      #
    la $t2, numbers      #
    add $t3, $t1, $t2    # $t3 = &numbers[i]
    lw $t6, ($t3)        # y = numbers[i]

    sub $t4, $t3, 4      # $t4 = &numbers[i - 1]
    lw $t7, ($t4)        # x = numbers[i - 1]

    bge $t6, $t7, loop1_increment   #  if (x < y) {
    li $t5, 1                       #  swapped = 1

loop1_increment:

    add $t0, $t0, 1      # i++;
    b loop1              # goto start of loop1
end1:

    move $a0, $t5       # load swapped into $a0
    li $v0, 1           # printf("%d", numbers[i])
    syscall

    li   $a0, '\n'      # printf("%c", '\n');
    li   $v0, 11
    syscall

    jr $ra              # return

   
.data

numbers:
    .word 0 0 0 0 0 0 0 0 0 0  # int numbers[10] = {0};

