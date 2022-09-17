#include "machine.h"
#include <stdio.h>

/* Name: Changlin Jiang
 * TerpConnect login ID: jiangcl
 * university ID: 117243543
 * Discussion section number: 0102
 * 
 * I pledge on my honor that I have not given or received any unauthorized
 * assistance on this assignment.
 */
 
 
/* This code extracts opcode, extension number, register being modified,
 * registers being read, and memory address(or immediate literal) from given
 * valid instruction.
 * 
 * This code is able to print the starting N2 memory address for an array
 * of instructions and each element of the instructions.
 * 
 * This code is also able to find the position of the register first being
 * given a value or set and check if the instruction program is safe or not.
 */




static int *check_valid_instruction(Wrd instruction, int *arr);

/* This helper function checks if the instruction is valid or not.    */
/* It creates an array for the fields of the instruction.             */
/* If valid, it returns an array that contains all used fields values */
/* and -1 values for the fields that are not used by instructions.    */
/* If not valid, it returns an array that contains all -1 values.     */
static int *check_valid_instruction(Wrd instruction, int *arr){

    /* pass in an array for the fields of the instruction            */
    /* position 0 is opcode; 1 is extension; 2 is write-register1    */
    /* 3 is read-register1; 4 is read-register2; 5 is read-register3 */
    /* 6 is address or immidiate value */
    
    
    /* use bit masking to extrac the values of fields from the instruction */
    unsigned int opcode_mask = 0xf8000000;
    unsigned int extension_mask = 0x07000000;
    unsigned int r1_mask = 0x00e00000;
    unsigned int r2_mask = 0x001c0000;
    unsigned int r3_mask = 0x00038000;
    unsigned int value_mask = 0x00007fff;
    unsigned int opcode, extension, r1, r2, r3, value;
    
    opcode = (instruction & opcode_mask) >> 27;
    extension = (instruction & extension_mask) >> 24;
    r1 = (instruction & r1_mask) >> 21;
    r2 = (instruction & r2_mask) >> 18;
    r3 = (instruction & r3_mask) >> 15;
    value = (instruction & value_mask);
    
    /* assign used values to the array if the instruction is valid */
    switch (opcode) {
    case PLUS: 
    case MINUS:
    case TIMES:
    case DIV:
    case MOD:
    case SHL:
    case SHR:
    case BAND:
    case BOR:
    case BXOR:
    case AND:
    case OR:
            if (r1 >= 0 && r1 < 6 && r2 >= 0 && r2 < 7 && r3 >= 0 && r3 < 7) {
                arr[0] = opcode;
                arr[2] = r1;
                arr[4] = r2;
                arr[5] = r3;
            }
            return arr;
    case NEG:
    case ABS:
    case BNEG:
    case NOT:
    case MOVE:
            if (r1 >= 0 && r1 < 6 && r2 >= 0 && r2 < 7) {
                arr[0] = opcode;
                arr[2] = r1;
                arr[4] = r2;
            }
            return arr;
    case EQ:
    case NEQ:
    case LE:
    case LT:
    case GE:
    case GT:
            if (r1 >= 0 && r1 < 6 && r2 >= 0 && r2 < 7 && (value % 4) == 0) {
                arr[0] = opcode;
                arr[3] = r1;
                arr[4] = r2;
                arr[6] = value;
            }
            return arr;
    case LW:
            if (r1 >= 0 && r1 < 6 && (value % 4) == 0) {
                arr[0] = opcode;
                arr[2] = r1;
                arr[6] = value;
            }
            return arr;
    case SW:
            if (r1 >= 0 && r1 < 6 && (value % 4) == 0) {
                arr[0] = opcode;
                arr[3] = r1;
                arr[6] = value;
            }
            return arr;
    case LI:
            if (r1 >= 0 && r1 < 6) {
                arr[0] = opcode;
                arr[2] = r1;
                arr[6] = value;
            }
            return arr;
    case SYS:
            if (extension >=0 && extension <= 4) {
                if (extension == 0 || extension == 2) {
                    arr[0] = opcode;
                    arr[1] = extension;
                    arr[2] = r1;
                }
                if (extension == 1 || extension == 3) {
                    arr[0] = opcode;
                    arr[1] = extension;
                    arr[3] = r1;
                }
                if (extension == 4){
                    arr[0] = opcode;
                    arr[1] = extension;
                }
            }
            return arr;
    default:
            return arr; 
    }
}



/* This function prints out the components of the instruction in one single 
 * line and components are separated by a space if the instruction is valid.
 * It returns 1 if the instruction is valid, returns 0 otherwise.
 */   
unsigned short print_instruction(Wrd instruction){
    /* use bit masking to extract the values of fields from the instruction */
    unsigned int opcode_mask = 0xf8000000;
    unsigned int extension_mask = 0x07000000;
    unsigned int r1_mask = 0x00e00000;
    unsigned int r2_mask = 0x001c0000;
    unsigned int r3_mask = 0x00038000;
    unsigned int value_mask = 0x00007fff;
    unsigned int opcode, extension, r1, r2, r3, value;
    int valid;
    int arr[7] = {-1, -1, -1, -1, -1, -1, -1};
    
    opcode = (instruction & opcode_mask) >> 27;
    extension = (instruction & extension_mask) >> 24;
    r1 = (instruction & r1_mask) >> 21;
    r2 = (instruction & r2_mask) >> 18;
    r3 = (instruction & r3_mask) >> 15;
    value = (instruction & value_mask);
    
    valid = check_valid_instruction(instruction, arr)[0];
    /* print out the instruction's components if it is valid */
    if (valid != -1) {
        switch (opcode) {
            case PLUS:
                        printf("%s R%d R%d R%d ", "plus", r1, r2, r3);
                        return 1;
            case MINUS:
                        printf("%s R%d R%d R%d ", "minus", r1, r2, r3);
                        return 1;
            case TIMES:
                        printf("%s R%d R%d R%d ", "times", r1, r2, r3);
                        return 1;
            case DIV:
                        printf("%s R%d R%d R%d ", "div", r1, r2, r3);
                        return 1;
            case MOD:
                        printf("%s R%d R%d R%d ", "mod", r1, r2, r3);
                        return 1;
            case NEG:
                        printf("%s R%d R%d ", "neg", r1, r2);
                        return 1;
            case ABS:
                        printf("%s R%d R%d ", "abs", r1, r2);
                        return 1;
            case SHL:
                        printf("%s R%d R%d R%d ", "SHL", r1, r2, r3);
                        return 1;
            case SHR:
                        printf("%s R%d R%d R%d ", "shr", r1, r2, r3);
                        return 1;
            case BAND:
                        printf("%s R%d R%d R%d ", "band", r1, r2, r3);
                        return 1;
            case BOR:
                        printf("%s R%d R%d R%d ", "bor", r1, r2, r3);
                        return 1;
            case BXOR:
                        printf("%s R%d R%d R%d ", "bxor", r1, r2, r3);
                        return 1;
            case BNEG:
                        printf("%s R%d R%d ", "bneg", r1, r2);
                        return 1;
            case AND:
                        printf("%s R%d R%d R%d ", "and", r1, r2, r3);
                        return 1;
            case OR:
                        printf("%s R%d R%d R%d ", "or", r1, r2, r3);
                        return 1;
            case NOT:
                        printf("%s R%d R%d ", "not", r1, r2);
                        return 1;
            case EQ:
                        printf("%s R%d R%d %05d ", "eq", r1, r2, value);
                        return 1;
            case NEQ:
                        printf("%s R%d R%d %05d ", "neq", r1, r2, value);
                        return 1;
            case LE:
                        printf("%s R%d R%d %05d ", "le", r1, r2, value);
                        return 1;
            case LT:
                        printf("%s R%d R%d %05d ", "lt", r1, r2, value);
                        return 1;
            case GE:
                        printf("%s R%d R%d %05d ", "ge", r1, r2, value);
                        return 1;
            case GT:
                        printf("%s R%d R%d %05d ", "gt", r1, r2, value);
                        return 1;
            case MOVE:
                        printf("%s R%d R%d ", "move", r1, r2);
                        return 1;
            case LW:
                        printf("%s R%d %05d", "lw", r1, value);
                        return 1;
            case SW:
                        printf("%s R%d %05d", "sw", r1, value);
                        return 1;
            case LI:
                        printf("%s R%d %d", "li", r1, value);
                        return 1;
            case SYS:
                        if (extension >=0 && extension <= 3)
                            printf("%s %d R%d ", "sys", extension, r1);
                        if (extension == 4)
                            printf("%s %d ", "sys", extension);
                        return 1;
        }
    }
    return 0;
}

/* This function prints out the starting N2 memory address in hexadecimal in 
 * four places(fill empty with zeros) and the components of the instruction 
 * if the instruction is valid.
 * It returns 1 if the instruction is valid, returns 0 otherwise.
 */ 
unsigned short disassemble(const Wrd program[], unsigned short num_instrs,
                           unsigned short *const bad_instr){
    int i, j, valid;
    
    /* return 0 if its parameters are invalid */
    if (program == NULL || bad_instr == NULL || num_instrs > NUM_WORDS)
        return 0;
    
    /* if not valid, store the first invalid instruction into bad_instr */
    /* and then return 0 */
    for (i = 0; i < num_instrs; i++) {
        int arr[7] = {-1, -1, -1, -1, -1, -1, -1};
        valid = check_valid_instruction(program[i], arr)[0];
        if (valid == -1) {
            *bad_instr = i;
            return 0;
        }
    }
    
    /* print out assembly language and instructions after they are converted */
    for (j = 0; j < num_instrs; j++) {
        printf("%04x: ", j*4);
        print_instruction(program[j]);
        printf("\n");
    }
    return 1;

}

/* This function returns the index in the array program of the first 
 * instruction where reg_nbr is given a value or set.
 * It returns -1 if its parameters are invalid, or reg_nbr is not a valid 
 * register number, or reg_nbr is not given a value or set.
 */ 
short where_set(const Wrd program[], unsigned short num_words,
                unsigned short reg_nbr){
    int i;
    int *instr_where;
    
    /* return -1 if its parameters are invalid */
    if (program == NULL || num_words > NUM_WORDS ||
         reg_nbr < 0 || reg_nbr > 5)
        return -1;
    
    /* check every instruction's write-register1 from the array        */
    /* and then compare with reg_nbr, return its position if it matchs */
    for (i = 0; i < num_words; i++) {
        int arr[7] = {-1, -1, -1, -1, -1, -1, -1};
        instr_where = check_valid_instruction(program[i], arr);
        if (instr_where[2] == reg_nbr)
            return i;
    }

    return -1;
}

/* This function returns 1 if the program that has pgm_size instructions is
 * safe, meaning that all instructions are valid and every register has been
 * set or given a value before it is used.
 * It returns 0 if its parameters are invalid, or any instruction is not a  
 * valid instruction, or this program is not safe.
 */ 
unsigned short is_safe(const Wrd program[], unsigned short pgm_size,
                       unsigned short *const bad_instr){
    int j, k, pos;
    int *instr;
    
    /* return 0 if its parameters are invalid */
    if (program == NULL || bad_instr == NULL || pgm_size > NUM_WORDS)
        return 0;

    /* Check every used register from each instruction                      */
    /* If any regester has not been set or given a value before it is used, */
    /* store the location of bad instruction into bad_instr and return 0    */
    for (j = 0; j < pgm_size; j++) {
        int arr[7] = {-1, -1, -1, -1, -1, -1, -1};
        instr = check_valid_instruction(program[j], arr);
        
        if (instr[0] == -1) 
            return 0;
            
        for (k = 3; k < 6; k++) {
            if (instr[k] != -1) {
                pos = where_set(program, pgm_size, instr[k]);
                if (pos == -1 || pos >= j) {
                *bad_instr = j;
                return 0;
                }
            }
        }
    }
    return 1;
}