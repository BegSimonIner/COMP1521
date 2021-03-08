# Lab 7 COMP1521
# Rifa Jamal z5311190 

# Sieve of Eratosthenes
# https://en.wikipedia.org/wiki/Sieve_of_Eratosthenes

# $s0 = i
# $s1 = j

main:
    li $t0, 1000

    #li $s0, 0           # int i = 0;

loop1:
    bge	$s0, $t0, endloop1

    la $t1, prime
    add $t1, $t1, $s0
    li $t3, 1
    sb	$t3, ($t1)          #prime[i] = 1

    addi $s0, $s0, 1
    b loop1

endloop1:
    
    li $s0, 2           # int i = 2

loop2_start:

    bge	$s0, $t0, end

if:
    lb	$t3, ($t1)	

    la $t1, prime
	add $t1, $t1, $s0
	lb $t3, ($t1)

    beq	$t3, $0, loop2_increment	# if  prime[i] == 0 then target
    
    move $a0, $s0           # printf(i)
    li    $v0, 1
    syscall

    li   $a0, '\n'      # printf("%c", '\n')
    li   $v0, 11
    syscall

    mul $s1, $s0, 2         #int j = 2*i

loop3:

    bge	$s1, 1000, loop2_increment	# if  >= $t1 then target
    
    # find prime[j] and set to 0

    # row offset
    la $t1, prime
    add $t1, $t1, $s1
    li $t3, 0
    sb	$t3, ($t1)          #prime[j] = 0

    add $s1, $s1, $s0
    b loop3

loop2_increment:

    addi $s0, $s0, 1
    b loop2_start

end:

    li $v0, 0           # return 0
    jr $31

.data
prime:
    .space 1000