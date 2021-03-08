#i in s0
#j in s1

main:

    # PUT YOUR CODE

    li $t0, 1000

loop0:

	bge $s0, $t0, endloop0

	la $t1, prime
	#mul $t2, $s0, 4
	add $t1, $t1, $s0

	li $t3, 1
	sb $t3, ($t1)

	addi $s0, $s0, 1

	b loop0

endloop0:

	li $s0, 2

loop1:

	bge $s0, $t0, endloop1

	la $t1, prime
	#mul $t2, $s0, 4
	add $t1, $t1, $s0
	lb $t3, ($t1)

	beq $t3, $0, if0

	move $a0, $s0
	li $v0, 1
	syscall

	li $a0, '\n'
	li $v0, 11
	syscall

	mul $s1, $s0, 2

loop2:

	bge $s1, $t0, endloop2

	la $t1, prime
	#mul $t2, $s1, 4
	add $t1, $t1, $s1

	li $t3, 0
	sb $t3, ($t1)

	add $s1, $s1, $s0

	b loop2

endloop2:

if0:

	addi $s0, $s0, 1

	b loop1

endloop1:


    li $v0, 0           # return 0
    jr $31

.data
prime:
    .space 1000


