// Assignment 2 - spims.c
// Written by Rifa Jamal z5311190
// COMP1521 20T2

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <assert.h>

#define MAX_INSTRUCTION_CODES 1000

//functions
void decode_instruction(uint32_t instruction);
int execute_instruction(uint32_t instruction, uint32_t registers[32], int *k);


int main(int arg, char *argv[]) {

    // check have command line argument
    FILE *stream = fopen(argv[1], "r");

    // check open succeeded

    int codes[MAX_INSTRUCTION_CODES];
    uint32_t registers[32] = { 0 };

    //loop - if successfully read
    //read from stream - hex into codes array
    //i < check won't overflow the array
    int n_instructions = 0;
    while (n_instructions < MAX_INSTRUCTION_CODES 
        && fscanf(stream, "%x", &codes[n_instructions]) == 1) { 
    
        n_instructions++;
    }

    printf("Program\n");
    for (int j = 0; j < n_instructions; j++) {
        //turn hex int mips code and print it
        if (j < 10 ) {
            printf("  %d: ", j);
        } else {
            printf(" %d: ", j);
        }
        decode_instruction(codes[j]);
        printf("\n");
    }

    printf("Output\n");
    int k = 0;
    while (k < n_instructions) {
        //turn hex int mips code and print it
        if (execute_instruction(codes[k], registers, &k) != 0) {
            break;
        }
        registers[0] = 0;
        /*
        int instruction_line = execute_instruction(codes[k], registers);
        //printf("\n");
        if (instruction_line) {
            k = k + instruction_line;
        } else {
            k++;
        }*/
        k++;
    }

    printf("Registers After Execution\n");
    int r_counter = 1;
    while (r_counter < 32) {
        if (registers[r_counter] != 0) {
            printf("$%-2d = %d\n", r_counter, registers[r_counter]);
        }
        
        r_counter++;
        
    }

}

int execute_instruction(uint32_t instruction, uint32_t registers[32], int *k) {

    //uint32_t instruction_line = 0;

    //if ori and $0 , make t = I
    //have other instructions

    // Find decimal values of different segments in instruction

    // Format Parts of R-type instruction code
    uint32_t opcode = (instruction >> 26);               // first 6 bits
    uint32_t d = (instruction >> 11) & 0x1F;             // second 5 bits
    uint32_t s = (instruction >> 21) & 0x1F;             // third 5 bits
    uint32_t t = (instruction >> 16) & 0x1F;             // fourth 5 bits
    uint32_t funct = instruction & 0x3F;                 // last 6 bits

    // Format Parts of J/I-type instruction code
    int16_t i = (instruction & 0xFFFF);                 // immediate address/ target
    //uint32_t result = 0;

    if (opcode == 0 && funct == 32) {
        // add $d, $s, $t
        // Bit Pattern: 000000ssssstttttddddd00000100000
        registers[d] = registers[s] + registers[t];
        
    } else if (opcode == 0 && funct == 34) {
        // sub $d, $s, $t
        // Bit Pattern: 000000ssssstttttddddd00000100010
        registers[d] = registers[s] - registers[t];

    } else if (opcode == 0 && funct == 36) {
        // and $d, $s, $t
        // Bit Pattern: 000000ssssstttttddddd00000100100
        registers[d] = registers[s] & registers[t];

    } else if (opcode == 0 && funct == 37) {
        // or $d, $s, $t
        // Bit Pattern: 000000ssssstttttddddd00000100101
        registers[d] = registers[s] | registers[t];

    } else if (opcode == 0 && funct == 42) {
        // slt $d, $s, $t
        // Bit Pattern: 000000ssssstttttddddd00000101010
        registers[d] = registers[s] < registers[t];

    } else if (opcode == 28 && funct == 2) {
        // mul $d, $s, $t
        // Bit Pattern: 011100ssssstttttddddd00000000010
        registers[d] = registers[s] * registers[t];

    } else if (opcode == 4) {
        // beq $s, $t, I
        // Bit Pattern: 000100ssssstttttIIIIIIIIIIIIIIII
        if (registers[s] == registers[t]) {
            //(instruction_line) += i << 2;
            //return (i << 2);

            //change i into 2's complement number

            //get top 16 bits of i
            //uint32_t mask_top = (i >> 16);
            //get sign of i 
            //uint32_t sign = i & 0x8000;

            /*if (sign == 1) {
                mask_top = 0xFFFF;
                i = i | (mask_top << 16);
            }*/
            *k = *k + (i-1);

        }
         
    } else if (opcode == 5) {
        // bne $s, $t, I
        // Bit Pattern: 000101ssssstttttIIIIIIIIIIIIIIII
        if (registers[s] != registers[t]) {
            //(instruction_line) += i << 2;

            ///change i into 2's complement number

            //get top 16 bits of i
            /*uint32_t mask_top = (i >> 16);
            //get sign of i 
            uint32_t sign = i & 0x8000;

            if (sign == 1) {
                mask_top = 0xFFFF;
                i = i | (mask_top << 16);
            }*/
            *k = *k + (i-1);
        }

    } else if (opcode == 8) {
        // addi $t, $s, I
        // Bit Pattern: 001000ssssstttttIIIIIIIIIIIIIIII
        //printf("%d %d", registers[t], registers[s]);
        registers[t] = registers[s] + i;
        
    } else if (opcode == 10) {
        // slti $t, $s, I
        // Bit Pattern: 001010ssssstttttIIIIIIIIIIIIIIII
        registers[t] = registers[s] < i;

    } else if (opcode == 12) {
        // andi $t, $s, I
        // Bit Pattern: 001100ssssstttttIIIIIIIIIIIIIIII
        registers[t] = registers[s] & i;

    } else if (opcode == 13) {
        // ori $t, $s, I
        // Bit Pattern: 001101ssssstttttIIIIIIIIIIIIIIII
        registers[t] = registers[s] | i;
        

    } else if (opcode == 15) {
        // lui $t, I
        // Bit Pattern: 00111100000tttttIIIIIIIIIIIIIIII
        registers[t] = i << 16;

    } else if (opcode == 14) {
        // xori $t, $s, I
        // Bit Pattern: 001110ssssstttttIIIIIIIIIIIIIIII
        registers[t] = registers[s] ^ i;

    } else if (opcode == 0 && funct == 0) {
        // sll $d, $t, I
        // Bit Pattern: 00000000000tttttdddddIIIII000000
        registers[d] = registers[t] << i;
        
    } else if (opcode == 0 && funct == 2) {
        // srl $d, $t, I
        // Bit Pattern: 00000000000tttttdddddIIIII000010
        registers[d] = registers[t] >> i;

    } else if (instruction == 12) {
        // Bit Pattern: 00000000000000000000000000001100
        // syscall

        // find v0 and a0
        uint32_t v0 = registers[2];
        uint32_t a0 = registers[4];
        
        if (v0 == 1) {
            // Print integer (in $a0 register)
            printf("%d", a0);
        } else if (v0 == 10) {
            // Exit
            return 1;
        } else if (v0 == 11) {
            // Print character
            printf("%c", a0);
        } else {
            printf("Unknown system call: %d\n", v0);
            return 1;
        }
    }

    return 0;

}

void decode_instruction(uint32_t instruction) {

    // Find decimal values of different segments in instruction

    // Format Parts of R-type instruction code
    int opcode = (instruction >> 26);               // first 6 bits
    int d = (instruction >> 11) & 0x1F;             // second 5 bits
    int s = (instruction >> 21) & 0x1F;             // third 5 bits
    int t = (instruction >> 16) & 0x1F;             // fourth 5 bits
    int funct = instruction & 0x3F;                 // last 6 bits

    // Format Parts of J/I-type instruction code
    int16_t i = (instruction & 0xFFFF);                 // immediate address/ target

    if (opcode == 0 && funct == 32) {
        // add $d, $s, $t
        // Bit Pattern: 000000ssssstttttddddd00000100000
        printf("add  $%d, $%d, $%d", d, s, t); 
    } else if (opcode == 0 && funct == 34) {
        // sub $d, $s, $t
        // Bit Pattern: 000000ssssstttttddddd00000100010
        printf("sub  $%d, $%d, $%d", d, s, t); 
    } else if (opcode == 0 && funct == 36) {
        // and $d, $s, $t
        // Bit Pattern: 000000ssssstttttddddd00000100100
        printf("and  $%d, $%d, $%d", d, s, t); 
    } else if (opcode == 0 && funct == 37) {
        // or $d, $s, $t
        // Bit Pattern: 000000ssssstttttddddd00000100101
        printf("or  $%d, $%d, $%d", d, s, t); 
    } else if (opcode == 0 && funct == 42) {
        // slt $d, $s, $t
        // Bit Pattern: 000000ssssstttttddddd00000101010
        printf("slt  $%d, $%d, $%d", d, s, t); 
    } else if (opcode == 28 && funct == 2) {
        // mul $d, $s, $t
        // Bit Pattern: 011100ssssstttttddddd00000000010
        printf("mul  $%d, $%d, $%d", d, s, t); 
    } else if (opcode == 4) {
        // beq $s, $t, I
        // Bit Pattern: 000100ssssstttttIIIIIIIIIIIIIIII
        printf("beq  $%d, $%d, %d", s, t, i); 
    } else if (opcode == 5) {
        // bne $s, $t, I
        // Bit Pattern: 000101ssssstttttIIIIIIIIIIIIIIII
        printf("bne  $%d, $%d, %d", s, t, i); 
    } else if (opcode == 8) {
        // addi $t, $s, I
        // Bit Pattern: 001000ssssstttttIIIIIIIIIIIIIIII
        printf("addi $%d, $%d, %d", t, s, i); 
    } else if (opcode == 10) {
        // slti $t, $s, I
        // Bit Pattern: 001010ssssstttttIIIIIIIIIIIIIIII
        printf("slti $%d, $%d, %d", t, s, i); 
    } else if (opcode == 12) {
        // andi $t, $s, I
        // Bit Pattern: 001100ssssstttttIIIIIIIIIIIIIIII
        printf("andi $%d, $%d, %d", t, s, i); 
    } else if (opcode == 13) {
        // ori $t, $s, I
        // Bit Pattern: 001101ssssstttttIIIIIIIIIIIIIIII
        printf("ori  $%d, $%d, %d", t, s, i); 
    } else if (opcode == 15) {
        // lui $t, I
        // Bit Pattern: 00111100000tttttIIIIIIIIIIIIIIII
        printf("lui  $%d, %d", t, i); 
    } else if (opcode == 14) {
        // xori $t, $s, I
        // Bit Pattern: 001110ssssstttttIIIIIIIIIIIIIIII
        printf("xori $%d, $%d, %d", t, s, i); 
    } else if (opcode == 0 && funct == 0) {
        // sll $d, $t, I
        // Bit Pattern: 00000000000tttttdddddIIIII000000
        printf("sll  $%d, $%d, %d", d, t, i); 
    } else if (opcode == 0 && funct == 2) {
        // srl $d, $t, I
        // Bit Pattern: 00000000000tttttdddddIIIII000010
        printf("srl  $%d, $%d, %d", d, t, i); 
    } else if (instruction == 12) {
        printf("syscall"); // Bit Pattern: 00000000000000000000000000001100
    }

}





















/*

// Assignment 2 - spims.c
// Written by Rifa Jamal z5311190
// COMP1521 20T2

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <assert.h>

#define MAX_INSTRUCTION_CODES 1000
#define MAX_REGISTERS 32

// R-Type Instruction Defines
#define ADD     32
#define SUB     34
#define AND     36
#define OR      37
#define SLT     42

// Syscall Defines
#define SYSCALL 12
#define REG_V0  2
#define REG_A0  4

// I/J-Type Instruction Defines
#define MUL     28
#define BEQ     4
#define BNE     5
#define ADDI    8
#define SLTI    10
#define ANDI    12
#define ORI     13
#define LUI     15

// Functions for Printing and Executing Mips Code
int instruction_start(uint32_t instruction);
void decode_r_type_instruction(uint32_t hex_instruction);
void decode_i_j_type_instruction(uint32_t hex_instruction);
//int execute_r_type_instruction(uint32_t hex_instruction, uint32_t registers[32]);
//int execute_i_j_type_instruction(uint32_t hex_instruction, uint32_t registers[32], int *k);
int execute_instruction(uint32_t instruction, uint32_t registers[32], int *k);

// Main

int main(int arg, char *argv[]) {

    // check have command line argument
    FILE *stream = fopen(argv[1], "r");

    // check open succeeded

    int codes[MAX_INSTRUCTION_CODES];
    uint32_t registers[32] = { 0 };

    //loop - if successfully read
    //read from stream - hex into codes array
    //i < check won't overflow the array
    int n_instructions = 0;
    while (n_instructions < MAX_INSTRUCTION_CODES 
        && fscanf(stream, "%x", &codes[n_instructions]) == 1) { 
    
        n_instructions++;
    }

    printf("Program\n");
    for (int j = 0; j < n_instructions; j++) {
        //turn hex int mips code and print it
        if (j < 10 ) {
            printf("  %d: ", j);
        } else {
            printf(" %d: ", j);
        }

        if (instruction_start(codes[j]) == 0) {
            decode_r_type_instruction(codes[j]);
        } else {
            decode_i_j_type_instruction(codes[j]);
        }
        
        printf("\n");
    }

    */

    /*
    printf("Output\n");
    int k = 0;
    while (k < n_instructions) {
        //turn hex int mips code and print it
        if (execute_instruction(codes[k], registers, &k) != 0) {
            break;
        }
        registers[0] = 0;
        k++;

        /*
        if (instruction_start(codes[k] == 0)) {
            if (execute_r_type_instruction(codes[k], registers) != 0) {
                break;
            }
        } else {
            execute_i_j_type_instruction(codes[k], registers, &k);
        }
        
        registers[0] = 0;
        k++;
        */

   // }


    

    /*
    printf("Registers After Execution\n");
    int r_counter = 1;
    while (r_counter < 32) {
        if (registers[r_counter] != 0) {
            printf("$%-2d = %d\n", r_counter, registers[r_counter]);
        }
        
        r_counter++;
        
    }

}

int instruction_start(uint32_t instruction) {
    uint32_t opcode = (instruction >> 26);               // first 6 bits
    return opcode;
}

int execute_instruction(uint32_t instruction, uint32_t registers[32], int *k) {

    uint32_t instruction_start = (instruction >> 26);               // first 6 bits
    uint32_t d = (instruction >> 11) & 0x1F;             // second 5 bits
    uint32_t s = (instruction >> 21) & 0x1F;             // third 5 bits
    uint32_t t = (instruction >> 16) & 0x1F;             // fourth 5 bits
    uint32_t instruction_end = instruction & 0x3F;                 // last 6 bits
    int16_t i = (instruction & 0xFFFF);                 // immediate address/ target
    
    if (instruction_end == ADD) {
        // add $d, $s, $t
        // Bit Pattern: 000000ssssstttttddddd00000100000
        registers[d] = registers[s] + registers[t];
        
    } else if (instruction_end == SUB) {
        // sub $d, $s, $t
        // Bit Pattern: 000000ssssstttttddddd00000100010
        registers[d] = registers[s] - registers[t];

    } else if (instruction_end == AND) {
        // and $d, $s, $t
        // Bit Pattern: 000000ssssstttttddddd00000100100
        registers[d] = registers[s] & registers[t];

    } else if (instruction_end == OR) {
        // or $d, $s, $t
        // Bit Pattern: 000000ssssstttttddddd00000100101
        registers[d] = registers[s] | registers[t];

    } else if (instruction_end == SLT) {
        // slt $d, $s, $t
        // Bit Pattern: 000000ssssstttttddddd00000101010
        registers[d] = registers[s] < registers[t];

    } else if (instruction_start == MUL) {
        // mul $d, $s, $t
        // Bit Pattern: 011100ssssstttttddddd00000000010
        registers[d] = registers[s] * registers[t];

    } else if (instruction_start == BEQ) {
        // beq $s, $t, I
        // Bit Pattern: 000100ssssstttttIIIIIIIIIIIIIIII
        if (registers[s] == registers[t]) {
            *k = *k + (i-1);

        }
         
    } else if (instruction_start == BNE) {
        // bne $s, $t, I
        // Bit Pattern: 000101ssssstttttIIIIIIIIIIIIIIII
        if (registers[s] != registers[t]) {
        
            *k = *k + (i-1);
        }

    } else if (instruction_start == ADDI) {
        // addi $t, $s, I
        // Bit Pattern: 001000ssssstttttIIIIIIIIIIIIIIII
        //printf("%d %d", registers[t], registers[s]);
        registers[t] = registers[s] + i;
        
    } else if (instruction_start == SLTI) {
        // slti $t, $s, I
        // Bit Pattern: 001010ssssstttttIIIIIIIIIIIIIIII
        registers[t] = registers[s] < i;

    } else if (instruction_start == ANDI) {
        // andi $t, $s, I
        // Bit Pattern: 001100ssssstttttIIIIIIIIIIIIIIII
        registers[t] = registers[s] & i;

    } else if (instruction_start == ORI) {
        // ori $t, $s, I
        // Bit Pattern: 001101ssssstttttIIIIIIIIIIIIIIII
        registers[t] = registers[s] | i;
        

    } else if (instruction_start == LUI) {
        // lui $t, I
        // Bit Pattern: 00111100000tttttIIIIIIIIIIIIIIII
        registers[t] = i << 16;

    } else if (instruction == SYSCALL) {
        // Bit Pattern: 00000000000000000000000000001100
        // syscall

        // find v0 and a0
        uint32_t v0 = registers[REG_V0];
        uint32_t a0 = registers[REG_A0];
        
        if (v0 == 1) {
            // Print integer (in $a0 register)
            printf("%d", a0);
        } else if (v0 == 10) {
            // Exit
            return 1;
        } else if (v0 == 11) {
            // Print character
            printf("%c", a0);
        } else {
            printf("Unknown system call: %d\n", v0);
            return 1;
        }
    }

    return 0;

}

*/

/*
int execute_r_type_instruction(uint32_t hex_instruction, uint32_t registers[32]) {

    // Format Parts of R-type instruction code
    uint32_t d = (hex_instruction >> 11) & 0x1F;             // second 5 bits
    uint32_t s = (hex_instruction >> 21) & 0x1F;             // third 5 bits
    uint32_t t = (hex_instruction >> 16) & 0x1F;             // fourth 5 bits
    uint32_t instruction = hex_instruction & 0x3F;           // last 6 bits

    if (instruction == ADD) {
        // add $d, $s, $t
        // Bit Pattern: 000000ssssstttttddddd00000100000
        registers[d] = registers[s] + registers[t];
        
    } else if (instruction == SUB) {
        // sub $d, $s, $t
        // Bit Pattern: 000000ssssstttttddddd00000100010
        registers[d] = registers[s] - registers[t];

    } else if (instruction == AND) {
        // and $d, $s, $t
        // Bit Pattern: 000000ssssstttttddddd00000100100
        registers[d] = registers[s] & registers[t];

    } else if (instruction == OR) {
        // or $d, $s, $t
        // Bit Pattern: 000000ssssstttttddddd00000100101
        registers[d] = registers[s] | registers[t];

    } else if (instruction == SLT) {
        // slt $d, $s, $t
        // Bit Pattern: 000000ssssstttttddddd00000101010
        registers[d] = registers[s] < registers[t];

    } else if (instruction == SYSCALL) {
        // syscall
        // Bit Pattern: 00000000000000000000000000001100
        
        // find registers v0 and a0
        uint32_t reg_v0 = registers[REG_V0];
        uint32_t reg_a0 = registers[REG_A0];
        
        if (reg_v0 == 1) {
            // Print integer (in $a0 register)
            printf("%d", reg_a0);
        } else if (reg_v0 == 10) {
            // Exit
            return 1;
        } else if (reg_v0 == 11) {
            // Print character
            printf("%c", reg_a0);
        } else {
            printf("Unknown system call: %d\n", reg_v0);
            return 1;
        }
    }

    return 0;
}

int execute_i_j_type_instruction(uint32_t hex_instruction, uint32_t registers[32], int *k) {

    uint32_t instruction = (hex_instruction >> 26);         // first 6 bits
    uint32_t d = (hex_instruction >> 11) & 0x1F;             // second 5 bits
    uint32_t s = (hex_instruction >> 21) & 0x1F;            // third 5 bits
    uint32_t t = (hex_instruction >> 16) & 0x1F;            // fourth 5 bits
    int16_t i = (hex_instruction & 0xFFFF);                 // immediate address/ target

    if (instruction == MUL) {
        // mul $d, $s, $t
        // Bit Pattern: 011100ssssstttttddddd00000000010
        registers[d] = registers[s] * registers[t];

    } else if (instruction == BEQ) {
        // beq $s, $t, I
        // Bit Pattern: 000100ssssstttttIIIIIIIIIIIIIIII
        if (registers[s] == registers[t]) {
            *k = *k + (i-1);
        }
         
    } else if (instruction == BNE) {
        // bne $s, $t, I
        // Bit Pattern: 000101ssssstttttIIIIIIIIIIIIIIII
        if (registers[s] != registers[t]) {
            *k = *k + (i-1);
        }

    } else if (instruction == ADDI) {
        // addi $t, $s, I
        // Bit Pattern: 001000ssssstttttIIIIIIIIIIIIIIII
        //printf("%d %d", registers[t], registers[s]);
        registers[t] = registers[s] + i;
        
    } else if (instruction == SLTI) {
        // slti $t, $s, I
        // Bit Pattern: 001010ssssstttttIIIIIIIIIIIIIIII
        registers[t] = registers[s] < i;

    } else if (instruction == ANDI) {
        // andi $t, $s, I
        // Bit Pattern: 001100ssssstttttIIIIIIIIIIIIIIII
        registers[t] = registers[s] & i;

    } else if (instruction == ORI) {
        // ori $t, $s, I
        // Bit Pattern: 001101ssssstttttIIIIIIIIIIIIIIII
        registers[t] = registers[s] | i;     

    } else if (instruction == LUI) {
        // lui $t, I
        // Bit Pattern: 00111100000tttttIIIIIIIIIIIIIIII
        registers[t] = i << 16;
    } 

    return 0;
}
*/

/*

void decode_r_type_instruction(uint32_t hex_instruction) {

    // Format Parts of R-type instruction code
    uint32_t d = (hex_instruction >> 11) & 0x1F;             // second 5 bits
    uint32_t s = (hex_instruction >> 21) & 0x1F;             // third 5 bits
    uint32_t t = (hex_instruction >> 16) & 0x1F;             // fourth 5 bits
    uint32_t instruction = hex_instruction & 0x3F;           // last 6 bits

    if (instruction == ADD) {
        // add $d, $s, $t
        // Bit Pattern: 000000ssssstttttddddd00000100000
        printf("add  $%d, $%d, $%d", d, s, t); 
    } else if (instruction == SUB) {
        // sub $d, $s, $t
        // Bit Pattern: 000000ssssstttttddddd00000100010
        printf("sub  $%d, $%d, $%d", d, s, t); 
    } else if (instruction == AND) {
        // and $d, $s, $t
        // Bit Pattern: 000000ssssstttttddddd00000100100
        printf("and  $%d, $%d, $%d", d, s, t); 
    } else if (instruction == OR) {
        // or $d, $s, $t
        // Bit Pattern: 000000ssssstttttddddd00000100101
        printf("or  $%d, $%d, $%d", d, s, t); 
    } else if (instruction == SLT) {
        // slt $d, $s, $t
        // Bit Pattern: 000000ssssstttttddddd00000101010
        printf("slt  $%d, $%d, $%d", d, s, t); 
    } else if (instruction == SYSCALL) {
        // Bit Pattern: 00000000000000000000000000001100
        printf("syscall"); 
    }
}

void decode_i_j_type_instruction(uint32_t hex_instruction) {

    uint32_t instruction = (hex_instruction >> 26);         // first 6 bits
    uint32_t d = (hex_instruction >> 11) & 0x1F;             // second 5 bits
    uint32_t s = (hex_instruction >> 21) & 0x1F;            // third 5 bits
    uint32_t t = (hex_instruction >> 16) & 0x1F;            // fourth 5 bits
    int16_t i = (hex_instruction & 0xFFFF);                 // immediate address/ target

    if (instruction == MUL) {
        // mul $d, $s, $t
        // Bit Pattern: 011100ssssstttttddddd00000000010
        printf("mul  $%d, $%d, $%d", d, s, t); 
    } else if (instruction == BEQ) {
        // beq $s, $t, I
        // Bit Pattern: 000100ssssstttttIIIIIIIIIIIIIIII
        printf("beq  $%d, $%d, %d", s, t, i); 
    } else if (instruction == BNE) {
        // bne $s, $t, I
        // Bit Pattern: 000101ssssstttttIIIIIIIIIIIIIIII
        printf("bne  $%d, $%d, %d", s, t, i); 
    } else if (instruction == ADDI) {
        // addi $t, $s, I
        // Bit Pattern: 001000ssssstttttIIIIIIIIIIIIIIII
        printf("addi $%d, $%d, %d", t, s, i); 
    } else if (instruction == SLTI) {
        // slti $t, $s, I
        // Bit Pattern: 001010ssssstttttIIIIIIIIIIIIIIII
        printf("slti $%d, $%d, %d", t, s, i); 
    } else if (instruction == ANDI) {
        // andi $t, $s, I
        // Bit Pattern: 001100ssssstttttIIIIIIIIIIIIIIII
        printf("andi $%d, $%d, %d", t, s, i); 
    } else if (instruction == ORI) {
        // ori $t, $s, I
        // Bit Pattern: 001101ssssstttttIIIIIIIIIIIIIIII
        printf("ori  $%d, $%d, %d", t, s, i); 
    } else if (instruction == LUI) {
        // lui $t, I
        // Bit Pattern: 00111100000tttttIIIIIIIIIIIIIIII
        printf("lui  $%d, %d", t, i); 
    }

}


*/

