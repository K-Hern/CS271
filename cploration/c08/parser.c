/****************************************
 * C-ploration 8 for CS 271
 * 
 * [NAME] $Kevin Hernandez$
 * [TERM] FALL $2023$
 * 
 ****************************************/
#include "parser.h"
#include "symtable.h"
#include "error.h"


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
    unsigned int label_line_num = 0;
    unsigned long instr_num = 0;


    while (fgets(line, sizeof(line), file)){

        if (instr_num > MAX_INSTRUCTIONS){
            exit_program(EXIT_TOO_MANY_INSTRUCTIONS, MAX_INSTRUCTIONS + 1);
        }
        strip(line);
        if (!(*line)){
            continue;
        }

        char inst_type = '\0';
        line_num ++;
        //printf("Current Label_line_num: %u\n",label_line_num);
        if (instr_num == 0)
        {
            line_num --;
        }

        if (is_Atype(line)){
            label_line_num ++; 
            //line_num ++;
            instr_num ++;
            inst_type = 'A';
            
           // printf("%c  %s\n", inst_type, line );
        }else if (is_label(line)){
            label_line_num ++; 
            //line_num ++;
            inst_type = 'L';
            char label[MAX_LABEL_LENGTH] = {0};
            extract_label(line, label);
            //printf("-------LABEL-----------  %u: %s\n",label_line_num, label);
            if(!(isalpha(label[0]))){
                exit_program(EXIT_INVALID_LABEL, (label_line_num + 2), label);
            }
            if(symtable_find(label) != NULL){
                exit_program(EXIT_SYMBOL_ALREADY_EXISTS, (label_line_num + 2), label);
            }
            symtable_insert(label, (instr_num));
            line_num --;
            continue;
            // printf("%c  %s\n", inst_type, label );

        }else //if (is_Ctype(line))
        {
            label_line_num ++; 
            //line_num ++;
            instr_num ++;
            inst_type = 'C';
            
           // printf("%c  %s\n", inst_type, line );
        }     
        //instr_num ++;
        printf("%u: %c  %s\n", line_num, inst_type, line);
        
    }

    

}
