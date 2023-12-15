/****************************************
 * Project 6 for CS 271
 * 
 * [NAME] $Kevin Hernandez$
 * [TERM] FALL $2023$
 * 
 ****************************************/
#include "parser.h"
#include "symtable.h"
#include "error.h"
#include "hack.h"

opcode instruction_to_opcode(c_instruction instr){
    opcode op = 0;
    ///I bit
    op |= (7 << 13);
    //a bit
    op |= (instr.a << 12);
    //comp bits
    op |= (instr.comp << 6);
    //dest bits
    op |= (instr.dest << 3);
    //jump bits
    op |= (instr.jump << 0);

    return op;
}

void assemble(const char * file_name, Instruction* instructions, int num_instructions){
    //Creating empty varibale to print later
    opcode Instruction_opcode;
    //int to track R[] of new variables
    int Reg_num = 16;
    //6 because 5 of ".hack" and '\0'
    int file_name_size = (strlen(file_name) + 6);
    char hack_file[file_name_size];
    strcpy(hack_file,file_name);
    strcat(hack_file, ".hack");

    FILE *fout = fopen(hack_file, "w" );
    int i = 0;


    fclose(fout);
}

void parse_C_instruction(char *line, c_instruction *instr){
    char line_breaker[] = ";";
    char line_breaker2[] = "=";
    char *temp;
    char *dest_token;
    char *jump_token;
    char *comp_token;
    //int *a = NULL;

    temp = strtok(line,line_breaker);
    jump_token = strtok(NULL, "");
    dest_token = strtok(temp,line_breaker2);
    comp_token = strtok(NULL, "");

  if(comp_token == NULL){
    comp_token = dest_token;
    dest_token = NULL;

  }


    int jump_result = str_to_jumpid(jump_token);
    short comp_result = str_to_compid(comp_token, instr->a);
    int dest_result = str_to_destid(dest_token);

    //printf("These are the token to be passed into .h Jump: '%d'\n, comp: '%d'\n, dest: '%d'\n", jump_result, comp_result, dest_result);

    instr->jump = jump_result;
    instr->comp = comp_result;
    instr->dest = dest_result;

      //printf("These are the values that have been passed into .h Jump: '%hd'\n, comp: '%hd'\n, dest: '%hd'\n", instr->jump, instr->comp, instr->dest);

}

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
    //s_end = '\0';

   //printf("1) This is s:'%s', this is line: '%s'\n", s, line+1);
    strcpy(s,(line+1));
    //printf("2) This is s:'%s', this is line: '%s'\n", s, line+1);

    long result = strtol(s, &s_end, 10);

    if (s == s_end){
        //Means we have a string
        instr->a_union.label = (char *) malloc(strlen(line));
        strcpy(instr->a_union.label,s);
        //printf("3) This is a_union.label:'%s'\n",  instr->a_union.label);
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
int parse(FILE * file, instruction_cat *Instructions){
	
    char line[MAX_LINE_LENGTH] = {0};
    unsigned int line_num = 0;
    unsigned long instr_num = 0;

 
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

        if (is_Atype(line)){

            //inst_type = 'A';

            if (!parse_A_instruction(line, &instr.itype.a_instruction)){
                exit_program(EXIT_INVALID_A_INSTR, line_num, line);
            }

            instr.type_of_inst = A_type_instruction;
            

            if (isdigit(line[1])) {
                //printf("A: %d\n", instr.itype.a_instruction.a_union.address);
            } else {
                //printf("A: %s\n", line + 1);
            }
    
            

        }else if (is_label(line)){

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

        }else{ //if (is_Ctype(line))

            char tmp_line[MAX_LINE_LENGTH];
            strcpy(tmp_line, line);
  
            parse_C_instruction(tmp_line, &instr.itype.c_instruction);

            if (instr.itype.c_instruction.dest == DEST_INVALID){
                exit_program(EXIT_INVALID_C_DEST, line_num, line);
            } else if (instr.itype.c_instruction.comp == COMP_INVALID) {
                exit_program(EXIT_INVALID_C_COMP, line_num, line);
            } else if (instr.itype.c_instruction.jump == JMP_INVALID) {
                exit_program(EXIT_INVALID_C_JUMP, line_num, line);
            }

            instr.type_of_inst = C_type_instruction;

        }  

        Instructions[instr_num ++] = instr;
    }

    return instr_num;
}
