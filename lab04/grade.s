# read a mark and print the corresponding UNSW grade
# written by Rifa Jamal COMP1521 z5311190

main:

    # name the mark entered
    li $t0, 0 #mark

    la $a0, prompt      # printf("Enter a mark: ");
    li $v0, 4
    syscall

    li $v0, 5           # scanf("%d", mark);
    syscall
    # move scanned in value into $t0 (name)
    move $t0, $v0


    # adding code from here
    # have if statements that is true, print and then goto end

    #if (mark < 50)
    #load number for $t1 (i.e. what you are checking
    li $t1, 50
    # need a brach to check
    blt	$t0, $t1, printfl	# if $t0 < $t1 then target
    
    #if we didn't branch the code will not to to printfl and keep going

    #if (mark < 65)
    li $t2, 65
    blt	$t0, $t2, printps	# if $t0 < $t1 then target

    #if (mark < 75)
    li $t3, 75
    blt	$t0, $t3, printcr	# if $t0 < $t1 then target

    #if (mark < 85)
    li $t4, 85
    blt	$t0, $t4, printdn	# if $t0 < $t1 then target

    #if (mark < 85)
    li $t4, 85
    blt	$t0, $t4, printdn	# if $t0 < $t1 then target
    
    #if (mark <= 100)
    li $t5, 100
    ble	$t0, $t5, printhd	# if  <= $t1 then target


printfl:    
    la $a0, fl          # printf("FL\n");
    li $v0, 4
    syscall
    jr $ra              # return

printps:    
    la $a0, ps          # printf("PS\n");
    li $v0, 4
    syscall
    jr $ra              # return

printcr:    
    la $a0, cr          # printf("PS\n");
    li $v0, 4
    syscall
    jr $ra              # return

printdn:    
    la $a0, dn          # printf("PS\n");
    li $v0, 4
    syscall
    jr $ra              # return

printhd:    
    la $a0, hd          # printf("PS\n");
    li $v0, 4
    syscall
    jr $ra              # return

    .data
prompt:
    .asciiz "Enter a mark: "
fl:
    .asciiz "FL\n"
ps:
    .asciiz "PS\n"
cr:
    .asciiz "CR\n"
dn:
    .asciiz "DN\n"
hd:
    .asciiz "HD\n"
