#mips minimum

.text
.globl main

main:

    li $t0, 0           # int x                
    li $t1, 0           # int y

    li  $v0, 5                  # scanf("%d", x);
    syscall
    move $t0, $v0

    li  $v0, 5                  # scanf("%d", y);
    syscall
    move $t1, $v0

    bge		$t1, $t0, print_y	# if y >= x then target

print_x:

    move $a0, $t0               # printf("%d", x); 
    li  $v0, 1
    syscall

    li   $a0, '\n'              # printf("%c", '\n');
    li   $v0, 11
    syscall

    j main_end

print_y:

    move $a0, $t0               # printf("%d", x); 
    li  $v0, 1
    syscall

    li   $a0, '\n'              # printf("%c", '\n');
    li   $v0, 11
    syscall

main_end:

    jr  $ra                     # return


###############################################################

#mipscounting (butnot13)

.text
.globl main

main:

    li $t0, 0                   # int x                
    li $t1, 0                   # int y

    li  $v0, 5                  # scanf("%d", x);
    syscall
    move $t0, $v0

    li  $v0, 5                  # scanf("%d", y);
    syscall
    move $t1, $v0

    addi $t2, $t0, 1			# $t2 = $t0 + 0
    
    bge	$t1, $t2, main_end	    # if $t1 >= 2t1main_endtarget
    
loop_start:

    beq		$t2, 13, loop_increment	# if $t2 == 13 then target
    
    move $a0, $t2               # printf("%d", x); 
    li  $v0, 1
    syscall

    li   $a0, '\n'              # printf("%c", '\n');
    li   $v0, 11
    syscall


loop_increment:

    addi	$t2, $t2, 1			# i++;
    j loop_start

main_end:

    jr  $ra                     # return


#######################################################################


#mipssquares

.text
.globl main

main:

    li $t0, 1                   # int x                

    li  $v0, 5                  # scanf("%d", x);
    syscall
    move $t0, $v0

    li $t1, 0                   # int i = 0  
    
loop1:

    bge	$t0, $t1, main_end	    # if x >= i then target
    li $t2, 0                   # int j = 0 

loop2:
    bge	$t0, $t2, loop1_increment	    # if x >= j then target
    
    li   $a0, '*'              # printf("%c", '*');
    li   $v0, 11
    syscall

loop2_increment:

    addi	$t2, $t2, 1			# j = j + 1
    j loop2

loop1_increment:

    addi	$t1, $t1, 1			# i = 1 + 1;
    
    li   $a0, '\n'              # printf("%c", '\n');
    li   $v0, 11
    syscall

    j loop1

main_end:

    jr  $ra                     # return


    


    