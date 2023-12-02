/****************************************
 * C-ploration 9 for CS 271
 * 
 * [NAME] $Kevin Hernandez$
 * [TERM] FALL $2023$
 * 
 ****************************************/
#include "parser.h"
#include "symtable.h"
#include "error.h"


void add_predefined_symbols(){
    int counter = 0;
    
    for(int i = 0; i < NUM_PREDEFINED_SYMBOLS; ++i){
    
        predefined_symbol symbol = predefined_symbols[counter];

        symtable_insert(symbol.name, symbol.address);
        counter ++;
    }
}

bool parse_A_instruction(const char *line, a_instruction *instr){

    
    char *s = (char*)malloc(strlen(line));
    char *s_end = (char*)malloc(strlen(line));
    s_end = '\0';


    strcpy(s,(line+1));

    long result = strtol(s, &s_end, 10);

    if (s == s_end){
        //Means we have a string
        instr->a_union.label = (char *) malloc(sizeof(line));
        strcpy(instr->a_union.label,s);
        instr->is_addr = false;

    }else if(*s_end != 0){
        //Means there is a mix of %s & int (Invalid Label)
        return false;
    }else{
       instr->a_union.address = result;
       instr->is_addr = true;
        
    }

    return true;
}


bool is_Atype(const char *line)
{
    if (line[0] == '@'){
        return true;
    }else{
        return false;
    }
}

bool is_label(const char *line)
   {
       if ((line[0] == '(') && (line[(strlen(line)-1)] == ')')){
           return true;
       }else{
           return false;
       }
   }

bool is_Ctype(const char *line)
   {
       if (!(is_Atype(line)) && (!(is_label(line)))){
           return true;
       }else{
           return false;
       }

   }


char *extract_label(const char *line, char* label)
{

    int i = 1;
    int label_len = (strlen(line) - 1);

    while (i < label_len)
    {
        label[i-1] = line[i];
        i++;
    }

    label[i] = '\0';


    //printf("This is the line: %s This is the Label: %s\n",line, label);
    return label;


}

/* Function: strip
 * -------------
 * remove whitespace and comments from a line
 *
 * s: the char* string to strip
 *
 * returns: the stripped char* string
 */
char *strip(char *s){	

	// your code here
    char s_new[strlen(s)+ 1];
    int i = 0;

    for (char *s2 = s; *s2; s2++){
        if ((*s2 == '/') && (*(s2 + 1) == '/'))
        {
            break;

        } else if (!(isspace(*s2))){
            s_new[i++] = *s2;

        }
    }
    s_new[i] = '\0';
    strcpy(s, s_new);
    return s;	
}

/* Function: parse
 * -------------
 * iterate each line in the file and strip whitespace and comments. 
 *
 * file: pointer to FILE to parse
 *
 * returns: nothing
 */
void parse(FILE * file){
	
    char line[MAX_LINE_LENGTH] = {0};
    unsigned int line_num = 0;
    unsigned long instr_num = 0;
    int instr_counter = 0;

    
    instruction_cat instr;

    add_predefined_symbols();
    //symtable_display_table();

    while (fgets(line, sizeof(line), file)){
        line_num ++; 

        if (instr_num > MAX_INSTRUCTIONS){
            exit_program(EXIT_TOO_MANY_INSTRUCTIONS, MAX_INSTRUCTIONS + 1);
        }
        strip(line);
        if (!(*line)){
            continue;
        }
        //declaring the variable to silence warning
        char inst_type;

        if (is_Atype(line)){
            instr_counter++;
            instr_num ++;
            if (instr_counter == 1){
                instr_num --;
            }
            inst_type = 'A';

            //if (!parse_A_instruction(line, &instr.instr.a)){
            if (!parse_A_instruction(line, &instr.itype.a_instruction)){
                exit_program(EXIT_INVALID_A_INSTR, line_num, line);
            }
            //instr.itype = INST_A;
            instr.type_of_inst = A_type_instruction;
            
           // printf("%c  %s\n", inst_type, line );
        }else if (is_label(line)){
            inst_type = 'L';
            char label[MAX_LABEL_LENGTH] = {0};
            extract_label(line, label);
            if(!(isalpha(label[0]))){
                exit_program(EXIT_INVALID_LABEL, (line_num), label);
            }
            if(symtable_find(label) != NULL){
                exit_program(EXIT_SYMBOL_ALREADY_EXISTS, (line_num), label);
            }
            symtable_insert(label, (instr_num+1));
            continue;

        }else //if (is_Ctype(line))
        {
            instr_counter++;
            instr_num ++;
            if (instr_counter == 1){
                instr_num --;
            }

            inst_type = 'C';
            
        }     
        //printf("%lu: %c  %s\n", (instr_num), inst_type, line);
        
    }

}
