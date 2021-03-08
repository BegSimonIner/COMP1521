// Assignment 2 - spims.c
// Written by Rifa Jamal z5311190
// COMP1521 20T2

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <assert.h>

#define MAX_INSTRUCTION_CODES 1000

//functions
void decode_instruction(int32_t instruction);
int execute_instruction(int32_t instruction, int registers[]);
int check_register(int32_t instruction);
int get_register(int register_number);
int save_register(int register_number, int value);


int main(int arg, char *argv[]) {

    // check have command line argument
    FILE *stream = fopen(argv[1], "r");

    // check open succeeded

    int codes[MAX_INSTRUCTION_CODES];
    
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
        printf("  %d: ", j);
        decode_instruction(codes[j]);
        printf("\n");
    }

    printf("Output\n");
    int k = 0;
    int *registers[32];
    int register_counter = 0;
    while (k < n_instructions) {

        // Store registers into array
        int value =  check_register(codes[k]);
        if (value != 0) {
            registers[register_counter] = value;
            register_counter++;
        }

        //turn hex int mips code and print it
        printf("  %d: ", k);
        int instruction_line = execute_instruction(codes[k], registers);
        printf("\n");

        k = k + instruction_line;
    }

    printf("Registers After Execution\n");
    int r_counter = 0;
    while (r_counter < 32) {
        if (registers[r_counter] != 0) {
            printf("$%d = %d", r_counter, registers[r_counter]);
        }
        r_counter++;
    }

}
/*
int check_register(int32_t instruction) {

    // check if ori instruction
    // ori $t, $s, I
    uint32_t d = (instruction >> 11) & 0x1F;             // second 5 bits
    uint32_t s = (instruction >> 21) & 0x1F;             // third 5 bits

    if (s == 0) {
        return d;
    } else {
        return 0;
    }
}*/

int get_register(int register_number) {
    assert(register_number >= 0 && register_number < 32);
    if (register_number == 0){
        registers[0] = 0;
        return 0;
    }
    return registers[register_number];
}

int save_register(int register_number, int value) {
    assert(register_number >= 0 && register_number < 32);
    if (register_number != 0) {
        registers[register_number] = value;
    }
}


int execute_instruction(int32_t instruction, int registers[]) {

    uint32_t instruction_line = 0;

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
    uint32_t i = (instruction & 0xFFFF);                 // immediate address/ target
    uint32_t result = 0;

    if (opcode == 0 && funct == 32) {
        // add $d, $s, $t
        // Bit Pattern: 000000ssssstttttddddd00000100000
        result = get_register(s) + get_register(t);
        save_register(d, result);

    } else if (opcode == 0 && funct == 34) {
        // sub $d, $s, $t
        // Bit Pattern: 000000ssssstttttddddd00000100010
        result = get_register(s) - get_register(t);
        save_register(d, result);

    } else if (opcode == 0 && funct == 36) {
        // and $d, $s, $t
        // Bit Pattern: 000000ssssstttttddddd00000100100
        result = get_register(s) & get_register(t);
        save_register(d, result);

    } else if (opcode == 0 && funct == 37) {
        // or $d, $s, $t
        // Bit Pattern: 000000ssssstttttddddd00000100101
        result = get_register(s) | get_register(t);
        save_register(d, result);

    } else if (opcode == 0 && funct == 42) {
        // slt $d, $s, $t
        // Bit Pattern: 000000ssssstttttddddd00000101010
        result = get_register(s) << get_register(t);
        save_register(d, result);

    } else if (opcode == 28 && funct == 2) {
        // mul $d, $s, $t
        // Bit Pattern: 011100ssssstttttddddd00000000010
        result = get_register(s) * get_register(t);
        save_register(d, result);

    } else if (opcode == 4) {
        // beq $s, $t, I
        // Bit Pattern: 000100ssssstttttIIIIIIIIIIIIIIII
        if (get_register(s) == get_register(t)) {
            (instruction_line) += i << 2;
        }
         
    } else if (opcode == 5) {
        // bne $s, $t, I
        // Bit Pattern: 000101ssssstttttIIIIIIIIIIIIIIII
        if (get_register(s) != get_register(t)) {
            (instruction_line) += i << 2;
        }

    } else if (opcode == 8) {
        // addi $t, $s, I
        // Bit Pattern: 001000ssssstttttIIIIIIIIIIIIIIII
        result = get_register(s) + i;
        save_register(t, result);
        
    } else if (opcode == 10) {
        // slti $t, $s, I
        // Bit Pattern: 001010ssssstttttIIIIIIIIIIIIIIII
        result = get_register(s) << i;
        save_register(t, result);

    } else if (opcode == 12) {
        // andi $t, $s, I
        // Bit Pattern: 001100ssssstttttIIIIIIIIIIIIIIII
        result = get_register(s) & i;
        save_register(t, result);

    } else if (opcode == 13) {
        // ori $t, $s, I
        // Bit Pattern: 001101ssssstttttIIIIIIIIIIIIIIII
        result = get_register(s) | i;
        save_register(t, result);

    } else if (opcode == 15) {
        // lui $t, I
        // Bit Pattern: 00111100000tttttIIIIIIIIIIIIIIII
        result = i << 16;
        save_register(t, result);

    } else if (opcode == 14) {
        // xori $t, $s, I
        // Bit Pattern: 001110ssssstttttIIIIIIIIIIIIIIII
        result = get_register(s) ^ i;
        save_register(t, result);

    } else if (opcode == 0 && funct == 0) {
        // sll $d, $t, I
        // Bit Pattern: 00000000000tttttdddddIIIII000000
        result = get_register(t) << i;
        save_register(d, result);

    } else if (opcode == 0 && funct == 2) {
        // srl $d, $t, I
        // Bit Pattern: 00000000000tttttdddddIIIII000010
        result = get_register(t) >> i;
        save_register(d, result);

    } else if (instruction == 12) {
        // Bit Pattern: 00000000000000000000000000001100
        // syscall

        int v0;
        int a0;

        // find v0 and a0
        v0 = registers[4];
        a0 = registers[2]; 
        
        if (v0 == 1) {
            // Print integer (in $a0 register)
            printf("%d", a0);
        } else if (v0 == 10) {
            // Exit
            return 1;
        } else if (v0 == 11) {
            // Print character
            printf("%c", a0);
        }
    }

    return instruction_line;

}

void decode_instruction(int32_t instruction) {

    // Find decimal values of different segments in instruction

    // Format Parts of R-type instruction code
    int opcode = (instruction >> 26);               // first 6 bits
    int d = (instruction >> 11) & 0x1F;             // second 5 bits
    int s = (instruction >> 21) & 0x1F;             // third 5 bits
    int t = (instruction >> 16) & 0x1F;             // fourth 5 bits
    int funct = instruction & 0x3F;                 // last 6 bits

    // Format Parts of J/I-type instruction code
    int i = (instruction & 0xFFFF);                 // immediate address/ target

    if (opcode == 0 && funct == 32) {
        // add $d, $s, $t
        // Bit Pattern: 000000ssssstttttddddd00000100000
        printf("add $%d, $%d, $%d", d, s, t); 
    } else if (opcode == 0 && funct == 34) {
        // sub $d, $s, $t
        // Bit Pattern: 000000ssssstttttddddd00000100010
        printf("sub $%d, $%d, $%d", d, s, t); 
    } else if (opcode == 0 && funct == 36) {
        // and $d, $s, $t
        // Bit Pattern: 000000ssssstttttddddd00000100100
        printf("and $%d, $%d, $%d", d, s, t); 
    } else if (opcode == 0 && funct == 37) {
        // or $d, $s, $t
        // Bit Pattern: 000000ssssstttttddddd00000100101
        printf("or $%d, $%d, $%d", d, s, t); 
    } else if (opcode == 0 && funct == 42) {
        // slt $d, $s, $t
        // Bit Pattern: 000000ssssstttttddddd00000101010
        printf("slt $%d, $%d, $%d", d, s, t); 
    } else if (opcode == 28 && funct == 2) {
        // mul $d, $s, $t
        // Bit Pattern: 011100ssssstttttddddd00000000010
        printf("mul $%d, $%d, $%d", d, s, t); 
    } else if (opcode == 4) {
        // beq $s, $t, I
        // Bit Pattern: 000100ssssstttttIIIIIIIIIIIIIIII
        printf("beq $%d, $%d, %d", s, t, i); 
    } else if (opcode == 5) {
        // bne $s, $t, I
        // Bit Pattern: 000101ssssstttttIIIIIIIIIIIIIIII
        printf("bne $%d, $%d, %d", s, t, i); 
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
        printf("ori $%d, $%d, %d", t, s, i); 
    } else if (opcode == 15) {
        // lui $t, I
        // Bit Pattern: 00111100000tttttIIIIIIIIIIIIIIII
        printf("lui $%d, %d", t, i); 
    } else if (opcode == 14) {
        // xori $t, $s, I
        // Bit Pattern: 001110ssssstttttIIIIIIIIIIIIIIII
        printf("xori $%d, $%d, %d", t, s, i); 
    } else if (opcode == 0 && funct == 0) {
        // sll $d, $t, I
        // Bit Pattern: 00000000000tttttdddddIIIII000000
        printf("sll $%d, $%d, %d", d, t, i); 
    } else if (opcode == 0 && funct == 2) {
        // srl $d, $t, I
        // Bit Pattern: 00000000000tttttdddddIIIII000010
        printf("srl $%d, $%d, %d", d, t, i); 
    } else if (instruction == 12) {
        printf("syscall"); // Bit Pattern: 00000000000000000000000000001100
    }

}