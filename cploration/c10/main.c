/****************************************
 * C-ploration 10 for CS 271
 * 
 * [NAME] $Kevin Hernandez$
 * [TERM] FALL $2023$
 * 
 ****************************************/
#include "parser.h"
#include "symtable.h"
#include "error.h"
#include "hack.h"

#define MAX_INSTRUCTION_COUNT 30000

//c10 final

int main(int argc, const char *argv[])
{	
    int num_instructions;
    struct instruction_cat *Instructions = malloc(MAX_INSTRUCTION_COUNT * sizeof(struct instruction_cat));


    // if (argc !=2){
    //     printf("Usage: %s [filename]\n", argv[0]);
    //     exit(EXIT_FAILURE);
    // }

    if (argc != 2) {
    // incorrect number of arguments
        exit_program(EXIT_INCORRECT_ARGUMENTS, argv[0]);        
    }  
    
    FILE *fin = fopen( argv[1], "r" );

    // if (fin == NULL){
    //     perror("Unable to open file!");
    //     exit(EXIT_FAILURE);
    // }

    if(fin == NULL){ 
        exit_program(EXIT_CANNOT_OPEN_FILE, argv[1]);
}

    num_instructions = parse(fin, Instructions);
    //symtable_print_labels();
 


    fclose(fin);

    free(Instructions);

    return 0;

			
}


