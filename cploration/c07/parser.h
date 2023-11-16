/****************************************
 * C-ploration 7 for CS 271
 * 
 * [NAME] $Kevin Hernandez$
 * [TERM] FALL $2023$
 * 
 ****************************************/
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <stdbool.h>
#include <stdint.h>

#define MAX_LINE_LENGTH  200
#define MAX_LABEL_LENGTH (MAX_LINE_LENGTH - 2)


/** function prototypes **/

typedef int16_t hack_addr;
typedef int16_t opcode;

char *extract_label(const char *line, char* label);

char *strip(char *s);

void parse(FILE * file);


bool is_Atype(const char *);
bool is_label(const char *);
bool is_Ctype(const char *);


enum Instruction {
    Invalid_instruction = -1,
    A_type_instruction,
    C_type_instruction
};

typedef struct c_instruction {
   opcode a:1;
   opcode comp:6;
   opcode dest:3;
   opcode jump:3;
} c_instruction;

typedef struct a_instruction {
   union
   {
        hack_addr address;
        char *label;
    };
    bool is_addr;
} a_instruction;

typedef struct instruction_cat {

    union
    {
        a_instruction a_instruction;
        c_instruction c_instruction;
    };
    enum Instruction type_of_inst;

}instruction_cat;

