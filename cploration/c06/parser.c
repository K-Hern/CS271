/****************************************
 * C-ploration 6 for CS 271
 * 
 * [NAME] $Kevin Hernandez$
 * [TERM] FALL $2023$
 * 
 ****************************************/
#include "parser.h"

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
	
	// your code here

    char line[MAX_LINE_LENGTH] = {0};

    while (fgets(line, sizeof(line), file)){
        char label[MAX_LABEL_LENGTH] = {0};
        strip(line);
        if (!(*line)){
            continue;

        }

        char inst_type;
        if (is_Atype(line)){
            inst_type = 'A';
            printf("%c  %s\n", inst_type, line );
        }else if (is_label(line)){
             inst_type = 'L';
             extract_label(line, label);
             printf("%c  %s\n", inst_type, label );

        }else if (is_Ctype(line)){
             inst_type = 'C';
            printf("%c  %s\n", inst_type, line );
        }      

    
    }


}
