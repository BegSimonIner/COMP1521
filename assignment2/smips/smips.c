
// COMP1521 20T2 Assignment 2 - smips.c
// Written by Rifa Jamal z5311190 on August 2020


//////////////////////////////////////////////////////////////////////////
//                           SMIPS.C                                    //    
//                                                                      //
// This program is an emulator for a small simple subset of the MIPS.   //
//                                                                      //
// The input for smips.c will be the 32-bit instruction                 //
// codes for MIPS instructions as hexadecimal numbers.                  //
//                                                                      //                    
// The output from smips.c is:                                          //
// The instruction (assempler) corresponding to each instruction code   //
// The output produced by syscalls when executing the MIPS instructions.//
// The register values when the program terminates.                     //
//                                                                      //
//////////////////////////////////////////////////////////////////////////

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <assert.h>

#define MAX_INSTRUCTION_CODES   1000
#define MAX_REGISTERS           32

// R-Type Instruction Defines
#define ADD                     32
#define SUB                     34
#define AND                     36
#define OR                      37
#define SLT                     42

// Syscall Defines
#define SYSCALL                 12
#define REG_V0                  2
#define REG_A0                  4

// I/J-Type Instruction Defines
#define MUL                     28
#define BEQ                     4
#define BNE                     5
#define ADDI                    8
#define SLTI                    10
#define ANDI                    12
#define ORI                     13
#define LUI                     15

// Instruction Component Defines
#define OPCODE_SHIFT            26
#define REG_D_SHIFT             11
#define REG_S_SHIFT             21
#define REG_T_SHIFT             16
#define REG_MASK                0x1F
#define FUNCT_MASK              0x3F
#define IMM_MASK                0xFFFF
     

// Functions for Printing and Executing Mips Code
void decode_instruction(uint32_t instruction);
int execute_instruction(uint32_t instruction, int32_t registers[32], int *k);

// Function to check for valid instruction inputs
int check_valid(uint32_t instruction);


//////////////////////////////////////////////////////////////////////
//                           MAIN                                   //
//                                                                  //
//  Main function reads the hexadecimal input into an array 'codes' // 
//  which then calls relevant functions to produce the output.      //
//                                                                  //
////////////////////////////////////////////////////////////////////// 


int main(int arg, char *argv[]) {

    // Read in command line argument
    FILE *stream = fopen(argv[1], "r");
    // Check if file read was successful 
    if (stream == NULL) {
        perror(argv[1]);
        exit(1);
    }

    // codes holds the hexadecimal values from input
    uint32_t codes[MAX_INSTRUCTION_CODES] = { 0 };

    // registers is an array of registers
    int32_t registers[MAX_REGISTERS] = { 0 };

    // loop - if successful, reads from stream: hex into 'codes' array
    // loop also makes sure of no overflow.
    int n_instructions = 0;
    while (n_instructions < MAX_INSTRUCTION_CODES 
        && fscanf(stream, "%x", &codes[n_instructions]) == 1) { 
        
        // Error Check: Valid instruction code
        // If instruction not valid, print error message and exit
        if (check_valid(codes[n_instructions]) != 0) {
            printf("%s:%d: invalid instruction code: %08X\n", 
                argv[1], (n_instructions + 1), codes[n_instructions]);
            exit(1);
        }
        
        n_instructions++;
    }

    // Error Check: if fscanf does not successfully read file,
    // print error message and exit program
    if ((fscanf(stream, "%x", &codes[n_instructions]) == 0)) {
        printf("%s:1: invalid instruction code: %08X\n", 
            argv[1], codes[n_instructions]);
        exit(1);
    }

    // Printing the hexadecimal instructions as Mips code
    printf("Program\n");
    for (int j = 0; j < n_instructions; j++) {
        if (j < 10 ) {
            printf("  %d: ", j);
        } else {
            printf(" %d: ", j);
        }
        decode_instruction(codes[j]);
        printf("\n");
    }

    // Executing the Mips code and printing the output
    printf("Output\n");
    // for coniditon makes sure that the program line counter is within boundaries 
    // such as after executing beq and bne instructions.
    for (int line = 0; line >= 0 && line < n_instructions; line++) {

        // If the function returns a value other than 0, either:
        // syscall called exit, or
        // syscall was given an invalid argument
        if (execute_instruction(codes[line], registers, &line) != 0) {
            break;
        }
        // register $0 will always be the value 0
        // even if the value was changed in the instructions
        registers[0] = 0;
    }

    // Printing all non-zero register values after execution
    printf("Registers After Execution\n");
    for (int r_counter = 1; r_counter < MAX_REGISTERS; r_counter++) {
        if (registers[r_counter] != 0) {
            printf("$%-2d = %d\n", r_counter, registers[r_counter]);
        }
    }

}

//////////////////////////////////////////////////////////////////
//                      CHECK_VALID                             //
//                                                              //
//  check_valid checks that if given a hexadecimal number that  //
//  does not correspond to an instruction in the MIPS subset,   //
//  1 will be returned and a error message will be printed.     //
//                                                              //
////////////////////////////////////////////////////////////////// 


int check_valid(uint32_t instruction) {
    
    // Find componenets of instruction
    // Operation code - first 6 bits
    uint32_t opcode = (instruction >> OPCODE_SHIFT);     
    // Function code - last 6 bits 
    uint32_t funct = instruction & FUNCT_MASK; 

    // Check if valid R-type instructions or Syscall       
    if (opcode == 0) {
        if (funct != ADD
            && funct != SUB
            && funct != AND
            && funct != OR
            && funct != SLT
            && funct != SYSCALL) {  

            return 1;
        } 
        // Check if valid I or J Type instruction
    } else if (opcode != MUL
                && opcode != BEQ
                && opcode != BNE
                && opcode != ADDI
                && opcode != SLTI
                && opcode != ANDI
                && opcode != ORI
                && opcode != LUI ) {   
        return 1;
    } 

    return 0;

}

//////////////////////////////////////////////////////////////////
//                    DECODE_INSTRUCTIONS                       //
//                                                              //
//     This function decodes then prints the                    //
//     instruction corresponding to each instruction code.      //
//                                                              //
////////////////////////////////////////////////////////////////// 

void decode_instruction(uint32_t instruction) {

    // Find componenets of instruction
    uint32_t opcode = (instruction >> OPCODE_SHIFT);        // first 6 bits
    uint32_t d = (instruction >> REG_D_SHIFT) & REG_MASK;   // second 5 bits
    uint32_t s = (instruction >> REG_S_SHIFT) & REG_MASK;   // third 5 bits
    uint32_t t = (instruction >> REG_T_SHIFT) & REG_MASK;   // fourth 5 bits
    uint32_t funct = instruction & FUNCT_MASK;              // last 6 bits
    int16_t i = (instruction & IMM_MASK);                   // immediate/ address

    // Check for R-type instructions or Syscall
    if (opcode == 0) {
        // Check variants of instructions that have a '000000' opcode
        if (funct == ADD) {
            // add $d, $s, $t
            printf("add  $%d, $%d, $%d", d, s, t); 
        } else if (funct == SUB) {
            // sub $d, $s, $t
            printf("sub  $%d, $%d, $%d", d, s, t); 
        } else if (funct == AND) {
            // and $d, $s, $t
            printf("and  $%d, $%d, $%d", d, s, t); 
        } else if (funct == OR) {
            // or $d, $s, $t
            printf("or  $%d, $%d, $%d", d, s, t); 
        } else if (funct == SLT) {
            // slt $d, $s, $t
            printf("slt  $%d, $%d, $%d", d, s, t); 
        } else if (funct == SYSCALL) {
            printf("syscall"); 
        }
        
        // Check for I/J-type instructions
    } else if (opcode == MUL) {
        // mul $d, $s, $t
        printf("mul  $%d, $%d, $%d", d, s, t); 
    } else if (opcode == BEQ) {
        // beq $s, $t, I
        printf("beq  $%d, $%d, %d", s, t, i); 
    } else if (opcode == BNE) {
        // bne $s, $t, I
        printf("bne  $%d, $%d, %d", s, t, i); 
    } else if (opcode == ADDI) {
        // addi $t, $s, I
        printf("addi $%d, $%d, %d", t, s, i); 
    } else if (opcode == SLTI) {
        // slti $t, $s, I
        printf("slti $%d, $%d, %d", t, s, i); 
    } else if (opcode == ANDI) {
        // andi $t, $s, I
        printf("andi $%d, $%d, %d", t, s, i); 
    } else if (opcode == ORI) {
        // ori $t, $s, I
        printf("ori  $%d, $%d, %d", t, s, i); 
    } else if (opcode == LUI) {
        // lui $t, I
        printf("lui  $%d, %d", t, i); 
    } 

}

/////////////////////////////////////////////////////////////////////
//                   EXECUTE_INSTRUCTIONS                          //
//                                                                 //
//  This function runs through and executes the Mips instructions. //
//  If there is a syscall, a relevant output will be produced      //
//  based on the request.                                          //
//                                                                 //
///////////////////////////////////////////////////////////////////// 

int execute_instruction(uint32_t instruction, int32_t registers[32], int *line) {

    // Find componenets of instruction
    uint32_t opcode = (instruction >> OPCODE_SHIFT);        // first 6 bits
    uint32_t d = (instruction >> REG_D_SHIFT) & REG_MASK;   // second 5 bits
    uint32_t s = (instruction >> REG_S_SHIFT) & REG_MASK;   // third 5 bits
    uint32_t t = (instruction >> REG_T_SHIFT) & REG_MASK;   // fourth 5 bits
    uint32_t funct = instruction & FUNCT_MASK;              // last 6 bits
    int16_t i = (instruction & IMM_MASK);                   // immediate/ address

    // Check for R-type instructions or Syscall  
    if (opcode == 0) {
        // Check variants of instructions that have a '000000' opcode
        if (funct == ADD) {
            // add $d, $s, $t
            registers[d] = registers[s] + registers[t];
            
        } else if (funct == SUB) {
            // sub $d, $s, $t
            registers[d] = registers[s] - registers[t];

        } else if (funct == AND) {
            // and $d, $s, $t
            registers[d] = registers[s] & registers[t];

        } else if (funct == OR) {
            // or $d, $s, $t
            registers[d] = registers[s] | registers[t];

        } else if (funct == SLT) {
            // slt $d, $s, $t
            registers[d] = registers[s] < registers[t];
        } else if (funct == SYSCALL) {
            // Syscall instruction
            // find v0 and a0
            int32_t v0 = registers[REG_V0];
            int32_t a0 = registers[REG_A0];
            
            if (v0 == 1) {
                // Print integer (in $a0 register)
                printf("%d", a0);
            } else if (v0 == 10) {
                // Exit
                return 1;
            } else if (v0 == 11) {
                // Print character (in $a0 register)
                // note: print lowest 8 bits for character
                printf("%c", (a0 & 0xFF));
            } else {
                // Else if system call is not valid,
                // print an error message and return to main
                printf("Unknown system call: %d\n", v0);
                return 1;
            }
        }
        // Check for I/J-type instructions
    } else if (opcode == MUL) {
        // mul $d, $s, $t
        registers[d] = registers[s] * registers[t];

    } else if (opcode == BEQ) {
        // beq $s, $t, I
        if (registers[s] == registers[t]) {
            // branch up or down instructions given by i
            // line is the program counter (PC)
            *line = *line + (i-1);
        }
         
    } else if (opcode == BNE) {
        // bne $s, $t, I
        if (registers[s] != registers[t]) {
            // branch up or down instructions given by i
            // line is the program counter (PC)
            *line = *line + (i-1);
        }

    } else if (opcode == ADDI) {
        // addi $t, $s, I
        registers[t] = registers[s] + i;
        
    } else if (opcode == SLTI) {
        // slti $t, $s, I
        registers[t] = registers[s] < i;

    } else if (opcode == ANDI) {
        // andi $t, $s, I
        registers[t] = registers[s] & i;

    } else if (opcode == ORI) {
        // ori $t, $s, I
        registers[t] = registers[s] | i;
        
    } else if (opcode == LUI) {
        // lui $t, I
        // shift on I as an unsigned value
        uint32_t unsigned_i = (instruction & IMM_MASK);            
        registers[t] = unsigned_i << 16;
    } 

    return 0;

}
