############################################################################
# COMP1521 20T2 --- assignment 1: a cellular automaton renderer
# Written by <<RIFA JAMAL (z5311190)>>, July 2020.

# This code runs a one-dimensional, three-neighbour cellular automaton.
# It examines its neighbours and its value in the previous generation. 
# It then follows a rule entered by the user, which is 
# applied to every cell to derive the value for the next generation


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


# Strings for main to check for valid entries:

prompt_world_size:	.asciiz "Enter world size: "
error_world_size:	.asciiz "Invalid world size\n"
prompt_rule:		.asciiz "Enter rule: "
error_rule:		.asciiz "Invalid rule\n"
prompt_n_generations:	.asciiz "Enter how many generations: "
error_n_generations:	.asciiz "Invalid number of generations\n"

###############################################################################
    .text
    .globl main

# MAIN

# Frame:		$fp, $ra
# Uses:         $a0, $a1, $v0
# Clobbers:     $a0, $a1

# Locals:
#	 	Register |	Name/Use
#       - $s0:		world_size
#       - $s1:		rule
#       - $s2:		n_generations
#		- $t9:		int g
#		- $t0:		int reverse

# Structure:
#		main
#       -> [prologue]
#		-> set_negative_generations
#       -> first_generation
# 		-> loop_run_generation_init
#       	-> loop_run_generation
#       -> check_reverse
#          	-> reverse_true_init
#           	-> reverse_true_start
#			-> reverse_false_init
#				-> reverse_false_start
#       -> main_end_1
#       -> main_end_2
#       -> main_end_3
#       -> main_end
#       -> [epilogue]

main:

        # [prologue] set up stack frame
        sw		$fp, -4($sp)							
        sw		$ra, -8($sp)							# return address
        la		$fp, -4($sp)
        addiu	$sp, $sp, -8

    
        #####################    Checking for valid entries   ###################################

        # Check for valid world size
        la  	$a0, prompt_world_size             		# printf("Enter world size: ");
        li  	$v0, 4
        syscall

        li  	$v0, 5                  				# scanf("%d", world_size);
        syscall
        move 	$s0, $v0								

        blt		$s0, MIN_WORLD_SIZE, main_end_1			# if $s0 < MIN_WORLD_SIZE then main_end_1
        bgt		$s0, MAX_WORLD_SIZE, main_end_1			# if $s0 > MAX_WORLD_SIZE then main_end_1
        
        # Check for valid rule
        la  	$a0, prompt_rule            			# printf("Enter rule: ");
        li  	$v0, 4
        syscall

        li  	$v0, 5                  				# scanf("%d", rule);
        syscall
        move 	$s1, $v0

        blt		$s1, MIN_RULE, main_end_2				# if $s1 < MIN_RULE then main_end_2
        bgt		$s1, MAX_RULE, main_end_2				# if $s1 > MAX_RULE then main_end_2

        # Check for valid generations
        la  	$a0, prompt_n_generations             	# printf("Enter how many generations: ");
        li  	$v0, 4
        syscall

        li  	$v0, 5                  				# scanf("%d", n_generations);
        syscall
        move 	$s2, $v0

        blt		$s2, MIN_GENERATIONS, main_end_3		# if $s2 < MIN_GENERATIONS then main_end_3
        bgt		$s2, MAX_GENERATIONS, main_end_3		# if $s2 > MAX_GENERATIONS then main_end_3

        li   	$a0, '\n'              					# printf("%c", '\n');
        li   	$v0, 11
        syscall

        ###################  Setting up for negative generations  ###########################
set_negative_generation:	
        # negative generations means show the generations in reverse

        li 		$t0, 0									# int reverse = 0;
        bge		$s2, 0, first_generation				# if n_generations >= 0 then first_generation
        
        li 		$t0, 1									# reverse = 1;
        mul 	$s2, $s2, -1							# n_generations = -n_generations

        ##########################  Set up generations  #################################
first_generation:
        # the first generation always has a only single cell which is alive
        # this cell is in the middle of the world

        # find address of middle cell in first generation
        li 		$t1, 0									# row position = 0
                                    
        li 		$t2, 2								
        div		$t3, $s0, $t2							# col position = world_size/2
        
        mul 	$t1, $t1, $s0							# row_offset = row_position * row_size
        mul 	$t3, $t3, 1								# column_offset = col_position * col_size
        add		$t4, $t1, $t3							# offset = row_offset + col_offset;

        la 		$t5, cells								# get address of 2d array, 'cells'
        add 	$t5, $t5, $t4							# offset = offset + array address
        li 		$t6, 1
        sb 		$t6, ($t5)								# save byte of 1 into address
    
loop_run_generation_init:
        li 		$t9, 1									# int g = 1

loop_run_generation:
        bgt		$t9, $s2, check_reverse					# if $s5 >$s2 then target
    
        # move values into $a registers to pass in arguments
        move 	$a0, $s0								# $a0 <- $s0 (world_size)
        move 	$a1, $s1								# $a1 <- $s1 (rule)
        move 	$a2, $t9								# $a2 <- $t9 (g (which_generation))

        jal 	run_generation
        add		$t9, $t9,  1							# g = g + 1;
        b		loop_run_generation					

check_reverse:
        bne		$t0, 1, loop_reverse_false_init			# if reverse != 1 then loop_reverse_false_init
    
loop_reverse_true_init:
        move 	$t9, $s2								# int g = n_generations

loop_reverse_true_start:
        blt		$t9, 0, main_end						# if g < 0 then main_end
        move 	$a0, $s0								# $a0 <- s0 (world_size)
        move 	$a1, $t9								# $a1 <- $t9 (int g)
        jal 	print_generation

        li 		$t8, 1
        sub		$t9, $t9, $t8							# g = g - 1
        j 		loop_reverse_true_start

loop_reverse_false_init:
        li 		$t9, 0									# int g = n_generations

loop_reverse_false_start:
        bgt		$t9, $s2, main_end						# if g > n_generation then main_end
        move 	$a0, $s0								# $a0 <- s0 (world_size)
        move 	$a1, $t9								# $a1 <- $s4 (int g)
        jal 	print_generation

        addi	$t9, $t9, 1								# g = g + 1;
        j 		loop_reverse_false_start

        # Note: all main ends at bottom of code

############################################################################################

# RUN_GENERATION

    # Given `world_size', `which_generation', and `rule', calculate
    # a new generation according to `rule' and store it in `cells'.

# Frame:        $fp, $ra, $s0, $s1, $s2, $s3, $s4, $s5
# Uses:         $a0, $a1, $v0, $s0, $s1, $s2, $s3, $s4, $s5
# Clobbers:     $a0, $a1

# Locals:
#	 	Register |	Name/Use
#       - $s0:		world_size
#       - $s1:		rule
#       - $s2:		n_generations
#		- $s3:		int left
#		- $s4:		int centre
#		- $s5:		int right
#		- $t9:		which_generation (int g passed from main)
#		- $t1:		int x

# Structure:
#		run_generation
#       -> [prologue]
#		-> run_generation_loop_init
#		-> run_generation_loop_start
#       -> run_generation_set_left
#       -> run_generation_set_centre
#       -> run_generation_set_right
#       -> run_generation_state
#       -> run_generation_bit
#       -> run_generation_set
#		-> run_generation_cells
#		-> run_generation_set_alive
#       -> run_generation_set_dead
#       -> run_generation_loop_increment
#       -> run_generation_loop_end
#       -> [epilogue]
    
run_generation:
        # [prologue]: set up stack frame
        sw		$fp, -4($sp)
        sw		$ra, -8($sp)							# return address
        sw		$s0, -12($sp)							# world_size
        sw		$s1, -16($sp)							# rule
        sw		$s2, -20($sp)							# n_generations
        sw		$s3, -24($sp)							# int left
        sw		$s3, -28($sp)							# int centre
        sw		$s5, -32($sp)							# int right
        la		$fp, -4($sp)
        addiu	$sp, $sp, -32

        # move $a registers back into original registers
        move 	$s0, $a0								# $a0 -> $s0 (world_size)
        move 	$s1, $a1								# $a1 -> $s1 (rule)
        move 	$t9, $a2								# $a2 -> $t9 (int g)

run_generation_loop_init:
        li 		$t1, 0									# int x	
run_generation_loop_start:
        bge		$t1, $s0, run_generation_loop_end		# if x >= world_size then target
        
        # set left cell
        li		$s3, 0									# int left
        ble		$t1, 0, run_generation_set_centre		# if x <= 0 then target
    
run_generation_set_left:
        # find address of LEFT neighbour cell// cells[which_generation - 1][x-1]
    
        move 	$t2, $t9								# find row position
        li		$t8, 1									# cells[which_generation - 1][...]
        sub		$t2, $t2, $t8							

        move	$t3, $t1								# find column position
        sub		$t3, $t3, $t8							# cells[...][x-1]
        
        mul 	$t2, $t2, $s0							# calculate row offset
        mul 	$t3, $t3, 1								# calculate column offset
        add		$t4, $t2, $t3							# add row and col offset

        la 		$t5, cells								# get address of 2d array
        add 	$t5, $t5, $t4							# add offset to array address
        
        lb		$t5, ($t5)								# load byte stored in $t5

        move 	$s3, $t5								# save value of left

run_generation_set_centre:

        # find address of CENTRE neighbour cell// cells[which_generation - 1][x]

        move 	$t2, $t9								# find row position
        li		$t8, 1						
        sub		$t2, $t2, $t8							# cells[which_generation - 1][...]

        move	$t3, $t1								# find column position
                                                        # cells[...][x]
        
        mul 	$t2, $t2, $s0							# calculate row offset
        mul 	$t3, $t3, 1								# calculate column offset
        add		$t4, $t2, $t3							# add row and col offset

        la 		$t5, cells								# get address of 2d array
        add 	$t5, $t5, $t4							# add offset to array address
        
        lb		$t5, ($t5)								# load byte stored in $t5
        
        move 	$s4, $t5								# save value of centre
        
        # set right cell
        li		$s5, 0									# int left
        move 	$t2, $s0								# $t2 = world_size
        li		$t8, 1
        sub 	$t2, $t2, $t8							# world_size - 1;
        
        bge		$t1, $t2, run_generation_state			# if x >= world_size-1 then target

run_generation_set_right:

        # find address of RIGHT neighbour cell// cells[which_generation - 1][x + 1]

        move 	$t2, $t9								# find row position
        li		$t8, 1									# cells[which_generation - 1][...]
        sub		$t2, $t2, $t8							

        move	$t3, $t1								# find column position
        addi	$t3, $t3, 1								# cells[...][x + 1]

        mul 	$t2, $t2, $s0							# calculate row offset
        mul 	$t3, $t3, 1								# calculate column offset
        add		$t4, $t2, $t3							# add row and col offset

        la 		$t5, cells								# get address of 2d array
        add 	$t5, $t5, $t4							# add offset to array address
        
        lb		$t5, ($t5)								# load byte stored in $t5

        move 	$s5, $t5								# save value of right

run_generation_state:
        # Convert the left, centre, and right states into one value.

        sll		$s3, $s3, 2 						    # shift left cell 2 bits left
        sll		$s4, $s4, 1								# shift centre cell 1 bit left
        sll		$s5, $s5, 0  							# shift right cell 0 bits left

        li 		$t2, 0									# int state
        or		$t2, $t2, $s3							# state |= left
        or		$t2, $t2, $s4							# state |= centre
        or		$t2, $t2, $s5							# state |= right

run_generation_bit:
        # check whether bit (1 << state) is set or not in the rule.
        # by testing the corresponding bit of the rule number.

        li 		$t3, 0									# int bit
        li 		$t4, 1
        sllv    $t3, $t4, $t2							# bit = 1 << state

run_generation_set:

        and 	$t5, $t3, $s1							# int set = bit & rule

run_generation_cells:
        # find address of cells[which_generation][x]

        # find row position
        move 	$t2, $t9								# row/ which generation is g value

        move	$t3, $t1								# column

        mul 	$t2, $t2, $s0							# calculate row offset
        mul 	$t3, $t3, 1								# calculate column offset
        add		$t4, $t2, $t3							# add row and col offset

        la 		$t6, cells								# get address of 2d array
        add 	$t6, $t6, $t4							# add offset to array address

run_generation_set_alive:
        # if the set value is 1, set cell to 'alive'
        beq		$t5, 0, run_generation_set_dead			# if set == 0 then set_dead

        li 		$t7, 1
        sb 		$t7, ($t6)								# set value/save byte of 1 into address
        j 		run_generation_loop_increment

run_generation_set_dead:
        # if the set value is 1, set cell to 'dead'
        li 		$t7, 0
        sb 		$t7, ($t6)								# set value/save byte of 1 into address

run_generation_loop_increment:

        addi	$t1, $t1, 1								# $t1 = $t1 + 1 -> x = x + 1
        j 		run_generation_loop_start

run_generation_loop_end:

        # [epilogue] tear down stack frame
        lw 		$s5, -28($fp)
        lw 		$s4, -24($fp)
        lw 		$s3, -20($fp)
        lw		$s2, -16($fp)
        lw		$s1, -12($fp)
        lw		$s0, -8($fp)
        lw		$ra, -4($fp)
        la		$sp, 4($fp)
        lw		$fp, ($fp)
        
        jr		$ra

#########################################################################################

    # PRINT_GENERATION

    # Given `world_size', and `which_generation', print out the
    # specified generation.
    
# Frame:        $fp, $ra, $s0
# Uses:         $a0, $a1, $v0, $s0
# Clobbers:     $a0, $a1

# Locals:
#	 	Register |	Name/Use
#       - $s0:		world_size
#		- $t1:		int x
#		- $t9:		which_generation (int g passed from main)

# Structure:
#		print_generation
#       -> [prologue]
#		-> print_generation_loop_init
#		-> print_generation_loop_start
#       -> print_alive
#       -> print_dead
#       -> print_generation_end
#       -> [epilogue]

print_generation:

        # [prologue] set up stack frame
        sw		$fp, -4($sp)
        sw		$ra, -8($sp)							# return address
        sw		$s0, -12($sp)							# world_size
        la		$fp, -4($sp)
        addiu	$sp, $sp, -12

        # move $a registers back into original registers
        move 	$s0, $a0								# $a0 -> s0 (world_size)
        move 	$t9, $a1								# $a1 -> $t9 (int g)

        # print which_generation number and tab

        move 	$a0, $t9              				 		
        li  	$v0, 1									# printf("%d\n", which_generation)
        syscall

        li   	$a0, '\t'              					# printf("%c", '\t');
        li   	$v0, 11
        syscall

print_generation_loop_init:
        li 		$t1, 0									# int x = 0

print_generation_loop_start:
        bge		$t1, $s0, print_generation_end			# if x >= world_size then target
            
        # find address of cells[which_generation][x]
        # find row position
        move 	$t2, $t9								# row position is g value

        move	$t3, $t1								# column position is x

        mul 	$t2, $t2, $s0							# calculate row offset
        mul 	$t3, $t3, 1								# calculate column offset
        add		$t4, $t2, $t3							# add row and col offset

        la 		$t6, cells								# get address of 2d array
        add 	$t6, $t6, $t4							# add offset to array address
        lb		$t7, ($t6)								# load 1 or 0 from cell address
        

        # check if cell is a 1 or 0
        bne		$t7, 1, print_dead						# if cell value != 1 then print_dead

print_alive:

        li   	$a0, ALIVE_CHAR              			# printf("%c", '\n');
        li   	$v0, 11
        syscall

        addi 	$t1, $t1, 1
        j print_generation_loop_start

print_dead:

        li   	$a0, DEAD_CHAR              			# printf("%c", '\n');
        li   	$v0, 11
        syscall

        addi 	$t1, $t1, 1
        j print_generation_loop_start

print_generation_end:

        li   	$a0, '\n'              					# printf("%c", '\n');
        li   	$v0, 11
        syscall

        # [epilogue] tear down stack frame
        lw		$s0, -8($fp)
        lw		$ra, -4($fp)
        la		$sp, 4($fp)
        lw		$fp, ($fp)
        
        jr		$ra

############################################################################################


main_end_1:
        la  	$a0, error_world_size        			# printf("Invalid world size");
        li  	$v0, 4
        syscall

        j   	main_end  

main_end_2:
        la  	$a0, error_rule             			# printf("Invalid rule");
        li  	$v0, 4
        syscall

        j   	main_end

main_end_3:

        la  	$a0, error_n_generations      			# printf("Invalid number of generations");
        li  	$v0, 4
        syscall

        j   	main_end

main_end:
        # [epilogue] tear down stack frame
        lw		$ra, -4($fp)
        la		$sp, 4($fp)
        lw		$fp, ($fp)
    
        li		$v0, 0
        jr		$ra
