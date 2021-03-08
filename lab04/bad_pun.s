# A MIPS program that prints out a phrase
# Lab 4 Rifa Jamal z5311190

# creation of strings
.data
# create a label
promp: .asciiz "I MIPS you!"
# ascii string, z means 0 terminated (NULL byte at end)
# if we didnt have the 'z' we'd need to put the NULL byte at the end ourselves


# since writing code, start with .text
# everything under .text header is code
.text

# good practice to have .global main but don't need it
.globl main

# entry point to function
main:

# we need to print a string
# need to use system call

# we need to write a string and tell syscall what to do
# do this by putting a value into $v0, 4
# value 4 inside v0 will tell syscall to print a string
# but we also need to tell it what string to print
# so we put a value into a0, a0 is the value to print
# we need to put address of string into a0 but before that
# we need to create a string (see above .text)

# dont want to use li, li is just a number, use la (load address)
la $a0, promp
li $v0, 4 # 4 is print string
syscall

# print a new line, new line is a character

li $a0, '\n'
li $v0, 11 #11 is for print char
syscall

# return 0;
# return value goes into v0
# set v0 to 0

li $v0, 0

# jr (jump register) to ra (return address)
jr $ra