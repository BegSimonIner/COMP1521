		la      $t1, cells              # cells[0][0]
        mul     $t2, $s5, 1             # $t2 = g*1
        add     $t3, $t2, $t1           # cells[g*1 + 0]
        sub     $t4, $t3, 1             # cells[(g*1-1) + 0]

        mul     $t5, $t0, 1             # $t5 = x*1
        add     $t6, $t5, $t4           # cells[(g*1-1) + (x*1)]
        sub     $t7, $t6, 1             # cells[(g*1-1) + (x*1-1)]

		la		$t1, cells
		#find row position
		sub		$t2, $s5, 1				# row = g - 1
		#find col position
		sub		$t3, $t0, 1				# col = x - 1
		#find address of row
		mul		$t2, $t2, $s0
		#find address of col
		mul		$t3, $t3, 1
		#add address of row and col
		add		$t4, $t2, $t3
		#add $t4 to address of cells, save into t4
		add		$t4, $t1, $t4	
		#load byte into $t4
		lb		$s2, ($$t4)		
		


	################################

	loop_run_gen:
        li      $s2, 0                  # int left = 0
        bge     $t0, $s0, end_generation        # if (x >= world_size) goto end_generation
        
        ble     $t0, 0, else_run_gen0   # if (x <= 0) goto else_run_gen0 
        
        la      $t1, cells              # cells[0][0]
        mul     $t2, $s5, 1             # $t2 = g*1
        add     $t3, $t2, $t1           # cells[g*1 + 0]
        sub     $t4, $t3, 1             # cells[(g*1-1) + 0]

        mul     $t5, $t0, 1             # $t5 = x*1
        add     $t6, $t5, $t4           # cells[(g*1-1) + (x*1)]
        sub     $t7, $t6, 1             # cells[(g*1-1) + (x*1-1)]

        lb      $s2, ($t7)              # left = cells[which_generation -1][x-1]
                                        # debugged, for left = cells[which_generation -1][x-1]

######################################33

		la      $t0, cells              # gets the base address ofthe array i.e memory gets element cells[0][0]
        
        div     $t1, $s0, 2             # world_size/2 
        mul     $t2, $t1, 1             # world_size/2 * 4 multiply by 4 to get the single byte 
        add     $t3, $t2, $t0           # cells[0 + world_size/2 * 4]

        li      $s3, 1
        sb      $s3, ($t3)              # cells[0 + world_size / 2] = 1;

########################################################################
# COMP1521 20T2 --- assignment 1: a cellular automaton renderer
#
# Written by <<RIFA JAMAL (z5311190)>>, July 2020.


# Maximum and minimum values for the 3 parameters.

MIN_WORLD_SIZE	=    1
MAX_WORLD_SIZE	=  128
MIN_GENERATIONS	= -256
MAX_GENERATIONS	=  256
MIN_RULE	=    0
MAX_RULE	=  255

# Characters used to print alive/dead cells.

ALIVE_CHAR	= '#'
DEAD_CHAR	= '.'

# Maximum number of bytes needs to store all generations of cells.

MAX_CELLS_BYTES	= (MAX_GENERATIONS + 1) * MAX_WORLD_SIZE

	.data

# `cells' is used to store successive generations.  Each byte will be 1
# if the cell is alive in that generation, and 0 otherwise.

cells:	.space MAX_CELLS_BYTES


# Some strings you'll need to use:

prompt_world_size:	.asciiz "Enter world size: "
error_world_size:	.asciiz "Invalid world size\n"
prompt_rule:		.asciiz "Enter rule: "
error_rule:		.asciiz "Invalid rule\n"
prompt_n_generations:	.asciiz "Enter how many generations: "
error_n_generations:	.asciiz "Invalid number of generations\n"

	.text
	.globl main

	#
	# REPLACE THIS COMMENT WITH A LIST OF THE REGISTERS USED IN
	# `main', AND THE PURPOSES THEY ARE ARE USED FOR
	#
	# YOU SHOULD ALSO NOTE WHICH REGISTERS DO NOT HAVE THEIR
	# ORIGINAL VALUE WHEN `run_generation' FINISHES
	#

main:

	# set up stack frame
	sw	$fp, -4($sp)							
	sw	$ra, -8($sp)							# return address
	sw	$s0, -12($sp)							# world_size
	sw	$s1, -16($sp)							# rule
	sw	$s2, -20($sp)							# n_generations
	sw	$s3, -24($sp)							# row_size
	sw	$s4, -28($sp)							# col_size
	sw	$s4, -32($sp)							# int g
	la	$fp, -4($sp)
	addiu	$sp, $sp, -32

	

    #####################    Checking for valid entries   ###################################

	# Check for valid world size
	la  $a0, prompt_world_size             		# printf("Enter world size: ");
    li  $v0, 4
    syscall

	li  $v0, 5                  				# scanf("%d", world_size);
    syscall
    move $s0, $v0

	blt	$s0, MIN_WORLD_SIZE, main_end_1			# if s < MIN_WORLD_SIZE then target
	bgt	$s0, MAX_WORLD_SIZE, main_end_1			# if s > MAX_WORLD_SIZE then target
	
	# Check for valid rule
	la  $a0, prompt_world_size            		# printf("Enter rule: ");
    li  $v0, 4
    syscall

	li  $v0, 5                  				# scanf("%d", rule);
    syscall
    move $s1, $v0

	blt	$s1, MIN_RULE, main_end_2				# if s < MIN_RULE then target
	bgt	$s1, MAX_RULE, main_end_2				# if s > MAX_RULE then target

	# Check for valid generations
	la  $a0, prompt_n_generations             	# printf("Enter how many generations: ");
    li  $v0, 4
    syscall

	li  $v0, 5                  				# scanf("%d", n_generations);
    syscall
    move $s2, $v0

	blt	$s2, MIN_GENERATIONS, main_end_3		# if s < MIN_GENERATIONS then target
	bgt	$s2, MAX_GENERATIONS, main_end_3		# if s > MAX_GENERATIONS then target

    ###################  Setting up for negative generations  ##############################
	
	li 		$t0, 0								# int reverse = 0
	bge		$s2, 0, row_and_column_size			# if $s0 >= 0 then target
	
	li 		$t0, 1								# reverse = 1
	mul 	$s2, $s2, -1						# n_generations = -n_generations
	

row_and_column_size:
	# find row size
	li 		$s3, 4								# int row_size = 1
	mul 	$s3, $s3, $s0						# i.e. row_size = 4 * number of elements in row
	# find column size
	li 		$s4, 4								# int col_size = 4


	# the first generation always has a only single cell which is alive
    # this cell is in the middle of the world
first_generation:

	# find address of middle cell in first generation (row)

	li 		$t0, 0								# row 1 is in 0th position
								
	li 		$t1, 2								# find column position
												# i.e. find middle of row (take floor value)
	div		$t2, $s0, $t1						# $t0 = $s0 / 2
	
	
	mul 	$t2, $t2, $s3						# calculate row offset
	mul 	$t3, $t3, $s4						# calculate column offset
	add		$t5, $t2, $t3						# add row and col offset

	#do i need s7 or t7 here?
	la 		$t6, cells							# get address of 2d array
	add 	$t6, $t6, $t5						# add offset to array address
	li 		$t7, 1
	sb 		$t7, ($t6)							# set value/save byte of 1 into address
	
loop_run_generation:
	
	li 		$s5, 1								# int g = 1
	bgt		$s5, $s2, check_reverse				# if $s5 >$s2 then target
	#add move
	jal 	run_generation
	add		$s5, $s5,  1						# s5= $s5 + 1
	b		loop_run_generation


check_reverse:

	bne		$t0, 1, reverse_false				# if $t0 != 1 then target
	
reverse_true:



reverse_false:


	# replace the syscall below with
	#
	# li	$v0, 0
	# jr	$ra
	#
	# if your code for `main' preserves $ra by saving it on the
	# stack, and restoring it after calling `print_world' and
	# `run_generation'.  [ there are style marks for this ]

	li	$v0, 10
	syscall

###################################################################################
###################################################################################

	#
	# Given `world_size', `which_generation', and `rule', calculate
	# a new generation according to `rule' and store it in `cells'.
	#

	#
	# REPLACE THIS COMMENT WITH A LIST OF THE REGISTERS USED IN
	# `run_generation', AND THE PURPOSES THEY ARE ARE USED FOR
	#
	# YOU SHOULD ALSO NOTE WHICH REGISTERS DO NOT HAVE THEIR
	# ORIGINAL VALUE WHEN `run_generation' FINISHES
	#

run_generation:

	# set up stack frame
	sw	$fp, -4($sp)							
	sw	$ra, -8($sp)							# return address
	sw	$s5, -12($sp)							# int left
	sw	$s6, -16($sp)							# int centre
	sw	$s7, -20($sp)							# int right
	#sw	$s8, -24($sp)							# state
	#sw	$s9, -28($sp)							# bit
	la	$fp, -4($sp)
	addiu	$sp, $sp, -28


run_generation_loop_start:

	# for loop
	li 	$t0, 0									# int x	
	bge	$t0, 0, run_generation_loop_end			# if $t0 >= 0 then target
	
	# set left cell

	li	$s5, 0									# int left
	ble	$t0, 0, run_generation_set_centre		# if $t0 <= 0 then target
	
run_generation_set_left:

	# find address of left cell// cells[which_generation - 1][x-1]

	# find row position
	li 		$t1, $s4							# row/ which generation is g value
	subi	$t1, $t1, 1							# $t1 = $t1 - 1

	li		$t2, $t0				
	subi	$t2, $t2, 1							# find column position
	
	mul 	$t1, $t1, $s3						# calculate row offset
	mul 	$t2, $t2, $s4						# calculate column offset
	add		$t3, $t2, $t1						# add row and col offset

	la 		$t4, cells							# get address of 2d array
	add 	$t4, $t4, $t3						# add offset to array address
	
	li 		$s5, $t4							# save address of left

run_generation_set_centre:

	# find address of CENTRE cell// cells[which_generation - 1][x]

	# find row position
	li 		$t1, $s4							# row/ which generation is g value
	subi	$t1, $t1, 1							# $t1 = $t1 - 1

	li		$t2, $t0							# find column position
	
	mul 	$t1, $t1, $s3						# calculate row offset
	mul 	$t2, $t2, $s4						# calculate column offset
	add		$t3, $t2, $t1						# add row and col offset

	la 		$t4, cells							# get address of 2d array
	add 	$t4, $t4, $t3						# add offset to array address
	
	li 		$s6, $t4							# save address of left


	# set right cell

	li	$s7, 0									# int left
	li 	$t1, $s0								# $t1 = world_size
	subi $t1, $t1, 1							# $t1 = $t1 - 1
	
	bge	$t0, $t1, run_generation_state			# if $t0 <= 0 then target

run_generation_set_right:

	# find address of right cell// cells[which_generation - 1][x]

	# find row position
	li 		$t1, $s4							# row/ which generation is g value
	subi	$t1, $t1, 1							# $t1 = $t1 - 1

	li		$t2, $t0							# find column position
	addi	$t2, $t2, 1							# $t2 = $t2 + 1
	
	
	mul 	$t1, $t1, $s3						# calculate row offset
	mul 	$t2, $t2, $s4						# calculate column offset
	add		$t3, $t2, $t1						# add row and col offset

	la 		$t4, cells							# get address of 2d array
	add 	$t4, $t4, $t3						# add offset to array address
	
	li 		$s7, $t4							# save address of left


run_generation_state:

	# shift left cell 2 bits left
	sll		$s5, $s5, 2 

	# shift centre cell 1 bit left
	sll		$s6, $s6, 1

	# shift right cell 0 bits left
	sll		$s7, $s7, 2  

	li 		$t1, 0								# int state
	or		$t1, $t1, $s5						# $t1 = $t1 | $s5
	or		$t1, $t1, $s6						# $t1 = $t1 | $s6
	or		$t1, $t1, $s7						# $t1 = $t1 | $s5

run_generation_bit:

	li 		$t2, 0								# int bit
	li 		$t3, 1

	sllv    $t2, $t3, $t1						# $t2 = 1 ($t3) << state ($t1)

run_generation_set:

	li 		$t4, 0								# int set
	and 	$t4, $t2, $s1						# set = bit & rule

run_generation_set_alive:

	bne		$t4, 1, run_generation_set_dead		# if $t4 != 1 then target

	# find address of cells[which_generation][x]
	# find row position
	li 		$t1, $s4							# row/ which generation is g value

	li		$t2, $t0							# find column position
	
	mul 	$t1, $t1, $s3						# calculate row offset
	mul 	$t2, $t2, $s4						# calculate column offset
	add		$t3, $t2, $t1						# add row and col offset

	la 		$t4, cells							# get address of 2d array
	add 	$t4, $t4, $t3						# add offset to array address

	li 		$t5, 0
	sb 		$t5, ($t4)							# set value/save byte of 1 into address

run_generation_set_dead:

	# find address of cells[which_generation][x]
	# find row position
	li 		$t1, $s4							# row/ which generation is g value

	li		$t2, $t0							# find column position
	
	mul 	$t1, $t1, $s3						# calculate row offset
	mul 	$t2, $t2, $s4						# calculate column offset
	add		$t3, $t2, $t1						# add row and col offset

	la 		$t4, cells							# get address of 2d array
	add 	$t4, $t4, $t3						# add offset to array address

	li 		$t5, 1
	sb 		$t5, ($t4)							# set value/save byte of 1 into address


run_generation_loop_increment:


	addi		$t0, $t0, 1						# $t0 = $t0 + 1
	j run_generation_loop_start

run_generation_loop_end:

	jr	$ra


#########################################################################################
#########################################################################################


	#
	# Given `world_size', and `which_generation', print out the
	# specified generation.
	#

	#
	# REPLACE THIS COMMENT WITH A LIST OF THE REGISTERS USED IN
	# `print_generation', AND THE PURPOSES THEY ARE ARE USED FOR
	#
	# YOU SHOULD ALSO NOTE WHICH REGISTERS DO NOT HAVE THEIR
	# ORIGINAL VALUE WHEN `print_generation' FINISHES
	#

print_generation:

	#
	# REPLACE THIS COMMENT WITH YOUR CODE FOR `print_generation'.
	#

	jr	$ra


main_end_1:
	la  $a0, error_world_size        # printf("Invalid world size");
	li  $v0, 4
	syscall

	j   main_end_common  

main_end_2:
	la  $a0, error_rule              # printf("Invalid rule");
	li  $v0, 4
	syscall

	j   main_end_common


main_end_common:
	li   $a0, '\n'      			 # printf("%c", '\n');
    li   $v0, 11
    syscall

	jr   $ra           				 # return










##################################################################################
##################################################################################



########################################################################
# COMP1521 20T2 --- assignment 1: a cellular automaton renderer
#
# Written by <<RIFA JAMAL (z5311190)>>, July 2020.


# Maximum and minimum values for the 3 parameters.

MIN_WORLD_SIZE	=    1
MAX_WORLD_SIZE	=  128
MIN_GENERATIONS	= -256
MAX_GENERATIONS	=  256
MIN_RULE	=    0
MAX_RULE	=  255

# Characters used to print alive/dead cells.

ALIVE_CHAR	= '#'
DEAD_CHAR	= '.'

# Maximum number of bytes needs to store all generations of cells.

MAX_CELLS_BYTES	= (MAX_GENERATIONS + 1) * MAX_WORLD_SIZE

	.data

# `cells' is used to store successive generations.  Each byte will be 1
# if the cell is alive in that generation, and 0 otherwise.

cells:	.space MAX_CELLS_BYTES


# Some strings you'll need to use:

prompt_world_size:	.asciiz "Enter world size: "
error_world_size:	.asciiz "Invalid world size\n"
prompt_rule:		.asciiz "Enter rule: "
error_rule:		.asciiz "Invalid rule\n"
prompt_n_generations:	.asciiz "Enter how many generations: "
error_n_generations:	.asciiz "Invalid number of generations\n"

	.text
	.globl main

	#
	# REPLACE THIS COMMENT WITH A LIST OF THE REGISTERS USED IN
	# `main', AND THE PURPOSES THEY ARE ARE USED FOR
	#
	# YOU SHOULD ALSO NOTE WHICH REGISTERS DO NOT HAVE THEIR
	# ORIGINAL VALUE WHEN `run_generation' FINISHES
	#

main:

	# set up stack frame
	sw	$fp, -4($sp)							
	sw	$ra, -8($sp)							# return address
	sw	$s0, -12($sp)							# world_size
	sw	$s1, -16($sp)							# rule
	sw	$s2, -20($sp)							# n_generations
	sw	$s3, -24($sp)							# row_size
	sw	$s4, -28($sp)							# col_size
	sw	$s5, -32($sp)							# int g
	la	$fp, -4($sp)
	addiu	$sp, $sp, -32

	

    #####################    Checking for valid entries   ###################################

	# Check for valid world size
	la  $a0, prompt_world_size             		# printf("Enter world size: ");
    li  $v0, 4
    syscall

	li  $v0, 5                  				# scanf("%d", world_size);
    syscall
    move $s0, $v0

	blt	$s0, MIN_WORLD_SIZE, main_end_1			# if s < MIN_WORLD_SIZE then target
	bgt	$s0, MAX_WORLD_SIZE, main_end_1			# if s > MAX_WORLD_SIZE then target
	
	# Check for valid rule
	la  $a0, prompt_world_size            		# printf("Enter rule: ");
    li  $v0, 4
    syscall

	li  $v0, 5                  				# scanf("%d", rule);
    syscall
    move $s1, $v0

	blt	$s1, MIN_RULE, main_end_2				# if s < MIN_RULE then target
	bgt	$s1, MAX_RULE, main_end_2				# if s > MAX_RULE then target

	# Check for valid generations
	la  $a0, prompt_n_generations             	# printf("Enter how many generations: ");
    li  $v0, 4
    syscall

	li  $v0, 5                  				# scanf("%d", n_generations);
    syscall
    move $s2, $v0

	blt	$s2, MIN_GENERATIONS, main_end_3		# if s < MIN_GENERATIONS then target
	bgt	$s2, MAX_GENERATIONS, main_end_3		# if s > MAX_GENERATIONS then target

    ###################  Setting up for negative generations  ##############################
	
	li 		$t0, 0								# int reverse = 0
	bge		$s2, 0, row_and_column_size			# if $s0 >= 0 then target
	
	li 		$t0, 1								# reverse = 1
	mul 	$s2, $s2, -1						# n_generations = -n_generations
	

row_and_column_size:
	# find row size
	li 		$s3, 4								# int row_size = 1
	mul 	$s3, $s3, $s0						# i.e. row_size = 4 * number of elements in row
	# find column size
	li 		$s4, 4								# int col_size = 4


	# the first generation always has a only single cell which is alive
    # this cell is in the middle of the world
first_generation:

	# find address of middle cell in first generation (row)

	li 		$t0, 0								# row 1 is in 0th position
								
	li 		$t1, 2								# find column position
												# i.e. find middle of row (take floor value)
	div		$t2, $s0, $t1						# $t0 = $s0 / 2
	
	
	mul 	$t2, $t2, $s3						# calculate row offset
	mul 	$t3, $t3, $s4						# calculate column offset
	add		$t5, $t2, $t3						# add row and col offset

	#do i need s7 or t7 here?
	la 		$t6, cells							# get address of 2d array
	add 	$t6, $t6, $t5						# add offset to array address
	li 		$t7, 1
	sb 		$t7, ($t6)							# set value/save byte of 1 into address
	
loop_run_generation:
	
	li 		$s5, 1								# int g = 1
	bgt		$s5, $s2, check_reverse				# if $s5 >$s2 then target
	
	# move values into $a registers to pass in arguments

	move 	$a0, $s0							# $a0 = s0
	move 	$a1, $s1							# $a1 = $s1
	move 	$a2, $s4							# $a2 = $s4

	jal 	run_generation
	add		$s5, $s5,  1						# s5= $s5 + 1
	b		loop_run_generation


check_reverse:

	bne		$t0, 1, reverse_false				# if $t0 != 1 then target
	
reverse_true:

	li 		$s4, $s2							# int g = n_generations
	blt		$s4, 0, main_end					# if $s4 < 0 then target
	
	move 	$a0, $s0							# $a0 = s0 (world_size)
	move 	$a1, $s4							# $a1 = $s4 (int g)

	jal print_generation

	subi	$s4, $s4, 1							# s4 = $s4 - 1
	j reverse_true

reverse_false:

	li 		$s4, 0								# int g = n_generations
	bgt		$s4, $s2, main_end					# if $s4 < $s2 then target
	
	move 	$a0, $s0							# $a0 = s0 (world_size)
	move 	$a1, $s4							# $a1 = $s4 (int g)

	jal print_generation

	addi	$s4, $s4, 1							# s4 = $s4 - 1
	j reverse_false

main_end:
	# replace the syscall below with
	#
	# li	$v0, 0
	# jr	$ra
	#
	# if your code for `main' preserves $ra by saving it on the
	# stack, and restoring it after calling `print_world' and
	# `run_generation'.  [ there are style marks for this ]

	li	$v0, 10
	syscall

###################################################################################
###################################################################################

	#
	# Given `world_size', `which_generation', and `rule', calculate
	# a new generation according to `rule' and store it in `cells'.
	#

	#
	# REPLACE THIS COMMENT WITH A LIST OF THE REGISTERS USED IN
	# `run_generation', AND THE PURPOSES THEY ARE ARE USED FOR
	#
	# YOU SHOULD ALSO NOTE WHICH REGISTERS DO NOT HAVE THEIR
	# ORIGINAL VALUE WHEN `run_generation' FINISHES
	#

run_generation:

	# set up stack frame
	sw	$fp, -4($sp)							
	sw	$ra, -8($sp)							# return address
	sw	$s5, -12($sp)							# int left
	sw	$s6, -16($sp)							# int centre
	sw	$s7, -20($sp)							# int right
	#sw	$s8, -24($sp)							# state
	#sw	$s9, -28($sp)							# bit
	la	$fp, -4($sp)
	addiu	$sp, $sp, -28


run_generation_loop_start:

	# for loop
	li 	$t0, 0									# int x	
	bge	$t0, 0, run_generation_loop_end			# if $t0 >= 0 then target
	
	# set left cell

	li	$s5, 0									# int left
	ble	$t0, 0, run_generation_set_centre		# if $t0 <= 0 then target
	
run_generation_set_left:

	# find address of left cell// cells[which_generation - 1][x-1]

	# find row position
	li 		$t1, $s4							# row/ which generation is g value
	subi	$t1, $t1, 1							# $t1 = $t1 - 1

	li		$t2, $t0				
	subi	$t2, $t2, 1							# find column position
	
	mul 	$t1, $t1, $s3						# calculate row offset
	mul 	$t2, $t2, $s4						# calculate column offset
	add		$t3, $t2, $t1						# add row and col offset

	la 		$t4, cells							# get address of 2d array
	add 	$t4, $t4, $t3						# add offset to array address
	
	li 		$s5, $t4							# save address of left

run_generation_set_centre:

	# find address of CENTRE cell// cells[which_generation - 1][x]

	# find row position
	li 		$t1, $s4							# row/ which generation is g value
	subi	$t1, $t1, 1							# $t1 = $t1 - 1

	li		$t2, $t0							# find column position
	
	mul 	$t1, $t1, $s3						# calculate row offset
	mul 	$t2, $t2, $s4						# calculate column offset
	add		$t3, $t2, $t1						# add row and col offset

	la 		$t4, cells							# get address of 2d array
	add 	$t4, $t4, $t3						# add offset to array address
	
	li 		$s6, $t4							# save address of left


	# set right cell

	li	$s7, 0									# int left
	li 	$t1, $s0								# $t1 = world_size
	subi $t1, $t1, 1							# $t1 = $t1 - 1
	
	bge	$t0, $t1, run_generation_state			# if $t0 <= 0 then target

run_generation_set_right:

	# find address of right cell// cells[which_generation - 1][x]

	# find row position
	li 		$t1, $s4							# row/ which generation is g value
	subi	$t1, $t1, 1							# $t1 = $t1 - 1

	li		$t2, $t0							# find column position
	addi	$t2, $t2, 1							# $t2 = $t2 + 1
	
	
	mul 	$t1, $t1, $s3						# calculate row offset
	mul 	$t2, $t2, $s4						# calculate column offset
	add		$t3, $t2, $t1						# add row and col offset

	la 		$t4, cells							# get address of 2d array
	add 	$t4, $t4, $t3						# add offset to array address
	
	li 		$s7, $t4							# save address of left


run_generation_state:

	# shift left cell 2 bits left
	sll		$s5, $s5, 2 

	# shift centre cell 1 bit left
	sll		$s6, $s6, 1

	# shift right cell 0 bits left
	sll		$s7, $s7, 2  

	li 		$t1, 0								# int state
	or		$t1, $t1, $s5						# $t1 = $t1 | $s5
	or		$t1, $t1, $s6						# $t1 = $t1 | $s6
	or		$t1, $t1, $s7						# $t1 = $t1 | $s5

run_generation_bit:

	li 		$t2, 0								# int bit
	li 		$t3, 1

	sllv    $t2, $t3, $t1						# $t2 = 1 ($t3) << state ($t1)

run_generation_set:

	li 		$t4, 0								# int set
	and 	$t4, $t2, $s1						# set = bit & rule

run_generation_set_alive:

	bne		$t4, 1, run_generation_set_dead		# if $t4 != 1 then target

	# find address of cells[which_generation][x]
	# find row position
	li 		$t1, $s4							# row/ which generation is g value

	li		$t2, $t0							# find column position
	
	mul 	$t1, $t1, $s3						# calculate row offset
	mul 	$t2, $t2, $s4						# calculate column offset
	add		$t3, $t2, $t1						# add row and col offset

	la 		$t4, cells							# get address of 2d array
	add 	$t4, $t4, $t3						# add offset to array address

	li 		$t5, 0
	sb 		$t5, ($t4)							# set value/save byte of 1 into address

run_generation_set_dead:

	# find address of cells[which_generation][x]
	# find row position
	li 		$t1, $s4							# row/ which generation is g value

	li		$t2, $t0							# find column position
	
	mul 	$t1, $t1, $s3						# calculate row offset
	mul 	$t2, $t2, $s4						# calculate column offset
	add		$t3, $t2, $t1						# add row and col offset

	la 		$t4, cells							# get address of 2d array
	add 	$t4, $t4, $t3						# add offset to array address

	li 		$t5, 1
	sb 		$t5, ($t4)							# set value/save byte of 1 into address


run_generation_loop_increment:


	addi		$t0, $t0, 1						# $t0 = $t0 + 1
	j run_generation_loop_start

run_generation_loop_end:

	jr	$ra


#########################################################################################
#########################################################################################


	#
	# Given `world_size', and `which_generation', print out the
	# specified generation.
	#

	#
	# REPLACE THIS COMMENT WITH A LIST OF THE REGISTERS USED IN
	# `print_generation', AND THE PURPOSES THEY ARE ARE USED FOR
	#
	# YOU SHOULD ALSO NOTE WHICH REGISTERS DO NOT HAVE THEIR
	# ORIGINAL VALUE WHEN `print_generation' FINISHES
	#

print_generation:

	#
	# REPLACE THIS COMMENT WITH YOUR CODE FOR `print_generation'.
	#

	move $a0, $a0              				 	# move value you're printing (i) to a0
    # li  $a0,                  				#printf("%d\n", i)
    li  $v0, 1
    syscall

    li   $a0, '\t'              				# printf("%c", '\t');
    li   $v0, 11
    syscall

	li 		$t0, 0								# int x = 0
	bge		$t0, $a0, print_generation_end	# if $t0 >= $t1 then target
	

	# find address of cells[which_generation][x]
	# find row position
	li 		$t1, $a1							# row/ which generation is g value

	li		$t2, $t0							# find column position
	
	mul 	$t1, $t1, $s3						# calculate row offset
	mul 	$t2, $t2, $s4						# calculate column offset
	add		$t3, $t2, $t1						# add row and col offset

	la 		$t4, cells							# get address of 2d array
	add 	$t4, $t4, $t3						# add offset to array address




	bne		$t0, $t1, target					# if $t0 != $t1 then target
	

print_generation_end:

	li   $a0, '\n'              				# printf("%c", '\n');
    li   $v0, 11
    syscall


	jr	$ra



############################################################################################


main_end_1:
	la  $a0, error_world_size        # printf("Invalid world size");
	li  $v0, 4
	syscall

	j   main_end_common  

main_end_2:
	la  $a0, error_rule              # printf("Invalid rule");
	li  $v0, 4
	syscall

	j   main_end_common


main_end_common:
	li   $a0, '\n'      			 # printf("%c", '\n');
    li   $v0, 11
    syscall

	jr   $ra           				 # return