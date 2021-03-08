# Read a number and print positive multiples of 7 or 11 < n

main:                   # int main(void) {

 # load counter
    li $s0, 1                   # i value
    #li $s1, 0                   # kind of like initialing a name for the number enetered

    la $a0, prompt      # printf("Enter a number: ");
    li $v0, 4
    syscall

    li $v0, 5           # scanf("%d", number);
    syscall
    move $s1, $v0       #move value of scanned number into $t1

loop__start:            # while loop starts here

    bge	$s0, $s1, end	    # if i > number then go to main__end

    rem $s2, $s0, 7           # $t3 = $t1 % $t2 (i % 7)
    beq	$s2, 0, print__number	# if t3 == 0 then target
    
    rem $s3, $s0, 11           # $t3 = $t1 % $t2 (i % 7)
    beq	$s3, 0, print__number	# if t3 == 0 then target
    
    #increment i
    addi	$s0, $s0, 1			# $t0 = $t0 + 1 (i = i + 1)
    # go back to start (of loop) using jump
    b loop__start	# jump to target

print__number:

    move $a0, $s0       #   printf("%d", i);
    li   $v0, 1
    syscall

    li   $a0, '\n'      # printf("%c", '\n');
    li   $v0, 11
    syscall

    addi	$s0, $s0, 1			# $t0 = $t0 + 1 (i = i + 1)
    b loop__start	# jump to target

end:
    jr   $ra           # return

    .data
prompt:
    .asciiz "Enter a number: "
