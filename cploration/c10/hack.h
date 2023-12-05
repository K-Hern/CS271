#ifndef __HACK_H__
#define __HACK_H__

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <stdbool.h>
#include <stdint.h>

#include "parser.h"

#define NUM_PREDEFINED_SYMBOLS 23
#define MAX_LINE_LENGTH  200
#define MAX_NAME_LENGTH (MAX_LINE_LENGTH - 2)

typedef enum symbol_id{
    SYM_R0 = 0,
    SYM_R1 = 1,
    SYM_R2,
    SYM_R3,
    SYM_R4,
    SYM_R5,
    SYM_R6,
    SYM_R7,
    SYM_R8,
    SYM_R9,
    SYM_R10,
    SYM_R11,
    SYM_R12,
    SYM_R13,
    SYM_R14,
    SYM_R15,
    SYM_SCREEN = 16384,
    SYM_KBD = 24576,
    SYM_SP = 0,
    SYM_LCL,
    SYM_ARG,
    SYM_THIS,
    SYM_THAT,

}symbol_id;


typedef struct predefined_symbol{
    char name[MAX_NAME_LENGTH];
    int16_t address;

}predefined_symbol;

static const predefined_symbol predefined_symbols[NUM_PREDEFINED_SYMBOLS] = {
    {"R0", SYM_R0},
    {"R1", SYM_R1},
    {"R2", SYM_R2},
    {"R3", SYM_R3},
    {"R4", SYM_R4},
    {"R5", SYM_R5},
    {"R6", SYM_R6},
    {"R7", SYM_R7},
    {"R8", SYM_R8},
    {"R9", SYM_R9},
    {"R10", SYM_R10},
    {"R11", SYM_R11},
    {"R12", SYM_R12},
    {"R13", SYM_R13},
    {"R14", SYM_R14},
    {"R15", SYM_R15},
    {"SCREEN", SYM_SCREEN},
    {"KBD", SYM_KBD},
    {"SP", SYM_SP},
    {"LCL", SYM_LCL},
    {"ARG", SYM_ARG},
    {"THIS", SYM_THIS},
    {"THAT", SYM_THAT}

};

typedef enum jump_id{
    JMP_INVALID = -1,
    JMP_NULL,
    JMP_JGT,
    JMP_JEQ,
    JMP_JGE,
    JMP_JLT,
    JMP_JNE,
    JMP_JLE,
    JMP_JMP
} jump_id;

typedef enum {
    DEST_INVALID = -1,
    DEST_NULL,
    DEST_M,
    DEST_D,
    DEST_DM,
    DEST_A,
    DEST_AM,
    DEST_AD,
    DEST_ADM,
}dest_id;

typedef enum {
    //a = 0
    COMP_INVALID = -1,
    COMP_0 = 42,
    COMP_1 = 63,
    COMP_NEG1 = 58,
    COMP_D = 12,
    COMP_A = 48,
    COMP_NOT_D = 13,
    COMP_NOT_A = 49,
    COMP_MINUS_D = 15,
    COMP_MINUS_A = 51,
    COMP_D_PLUS_1 = 31,
    COMP_A_PLUS_1 = 55,
    COMP_D_MINUS_1 = 14,
    COMP_A_MINUS_1 = 50,
    COMP_D_PLUS_A = 2,
    COMP_D_MINUS_A = 19,
    COMP_A_MINUS_D = 7,
    COMP_D_AND_A = 0,
    COMP_D_OR_A = 21,
    //a = 1
    COMP_M = 112,//a
    COMP_NOT_M = 113,//!a
    COMP_MINUS_M = 115,//_MINUS_a
    COMP_M_PLUS_1 = 119,//A_PLUS_1
    COMP_M_MINUS_1 = 114,//A_MINUS_1
    COMP_D_PLUS_M = 66,//D_PLUS_A
    COMP_D_MINUS_M = 83,//D_MINUS_A
    COMP_M_MINUS_D = 71,//A_MINUS_D
    COMP_D_AND_M = 64,//D_AND_A
    COMP_D_OR_M = 85,//D_OR_A

}comp_id;


static inline jump_id str_to_jumpid(const char *s){

    jump_id id = JMP_INVALID;

    if (s == NULL) {
        id = JMP_NULL;
    } else if ((strstr(s, "JGT")) != NULL) {
        id = JMP_JGT;
    } else if ((strstr(s, "JEQ")) != NULL) {
        id = JMP_JEQ;
    } else if ((strstr(s, "JGE")) != NULL) {
        id = JMP_JGE;
    } else if ((strstr(s, "JLT")) != NULL) {
        id = JMP_JLT;
    } else if ((strstr(s, "JNE")) != NULL) {
        id = JMP_JNE;
    } else if ((strstr(s, "JLE")) != NULL) {
        id = JMP_JLE;
    } else{
        id = JMP_JMP;
    }

    return id;
}

static inline dest_id str_to_destid(const char *s){
    
    dest_id id = DEST_INVALID;

    if (s == NULL) {
        id = DEST_NULL;
    } else if ((strstr(s, "M=")) != NULL) {
        id = DEST_M;
    } else if ((strstr(s, "D=")) != NULL) {
        id = DEST_D;
    } else if ((strstr(s, "DM=")) != NULL) {
        id = DEST_DM;
    } else if ((strstr(s, "A=")) != NULL) {
        id = DEST_A;
    } else if ((strstr(s, "AM=")) != NULL) {
        id = DEST_AM;
    } else if ((strstr(s, "AD=")) != NULL) {
        id = DEST_AD;
    } else{
        id = DEST_ADM;
    }

    return id;

}

static inline comp_id str_to_compid(const char *s, int *a){
    comp_id id = COMP_INVALID;

    if (s == NULL) {
        id = DEST_NULL;
    } else if ((strstr(s, "M=")) != NULL) {
        id = DEST_M;
    } else if ((strstr(s, "D=")) != NULL) {
        id = DEST_D;
    } else if ((strstr(s, "DM=")) != NULL) {
        id = DEST_DM;
    } else if ((strstr(s, "A=")) != NULL) {
        id = DEST_A;
    } else if ((strstr(s, "AM=")) != NULL) {
        id = DEST_AM;
    } else if ((strstr(s, "AD=")) != NULL) {
        id = DEST_AD;
    } else{
        id = DEST_ADM;
    }

    if (id > 63){
        *a = 1;
    }
    return id;

}

#endif