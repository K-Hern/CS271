/****************************************
 * C-ploration 9 for CS 271
 * 
 * [NAME] $Kevin Hernandez$
 * [TERM] FALL $2023$
 * 
 ****************************************/

#ifndef __PARSER_H__
#define __PARSER_H__

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <stdbool.h>
#include <stdint.h>

#include "hack.h"

#define MAX_LINE_LENGTH  200
#define MAX_LABEL_LENGTH (MAX_LINE_LENGTH - 2)

#define MAX_HACK_ADDRESS INT16_MAX
#define MAX_INSTRUCTIONS (MAX_HACK_ADDRESS)


/** function prototypes **/

typedef int16_t hack_addr;
typedef int16_t opcode;

char *extract_label(const char *line, char* label);

char *strip(char *s);

void parse(FILE * file);

bool is_Atype(const char *);
bool is_label(const char *);
bool is_Ctype(const char *);


typedef enum Instruction {
    Invalid_instruction = -1,
    A_type_instruction,
    C_type_instruction
}Instruction;

typedef struct c_instruction {
   opcode a:1;
   opcode comp:7;
   opcode dest:4;
   opcode jump:4;
} c_instruction;

typedef struct a_instruction {
   union {
        hack_addr address;
        char *label;
    }a_union;

    bool is_addr;
} a_instruction;

typedef struct instruction_cat {

    union
    {
        a_instruction a_instruction;
        c_instruction c_instruction;
    }itype;
    Instruction type_of_inst;

}instruction_cat;

void add_predefined_symbols();

bool parse_A_instruction(const char *line, a_instruction *instr);


#endif