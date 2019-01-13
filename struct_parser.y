%{
#include <stdio.h>
#include <string.h>

#include "struct_table.h"

extern "C"
{
int yyparse(void);
int yylex(void);  
void yyerror(const char *str)
{
        fprintf(stderr,"error: %s\n",str);
}
        
int yywrap()
{
        return 1;
} 

sentence_t current;

main()
{       
        sentence_clean(&current);
        struct_table_init(); // init defenitions store

        yyparse();        // parse input and push info to store

        struct_table_run();  // process with parser results
}

}

%}

%token INT;
%token LONG;
%token UNSIGNED;

%token STRUCT_DEC
%token UNION_DEC

%union
{
        unsigned unumber;
        char*    strptr;
}

%token <number> NUMBER
%token <strptr> WORD

%%
commands: /* empty */
        | commands declaration_op
        ;

declaration:
        base_types WORD { sentence_set_name(&current, $2); }
        | base_types '*' WORD  { sentence_set_ptr(&current);
                                 sentence_set_name(&current, $3); }
        | struct_definition WORD { sentence_set_type(&current, STRUCT_L); 
                                   sentence_set_name(&current, $2); }
        | struct_definition '*'  WORD { sentence_set_ptr(&current);
                                   sentence_set_type(&current, STRUCT_L);
                                   sentence_set_name(&current, $3); }
        | union_definition WORD { sentence_set_type(&current, UNION_L); 
                                   sentence_set_name(&current, $2); }
        | union_definition '*' WORD { sentence_set_ptr(&current);
                                   sentence_set_type(&current, UNION_L);
                                   sentence_set_name(&current, $3); }
        ;

declaration_op:
        declaration ';' { add_variable(&current); }                 /* <type_def> <name> ; */
        | struct_definition ';' { /*add_user_type(&current);*/ }    /* struct { <elements> } ; */
        | union_definition ';' { /*add_user_type(&current);*/ }     /* union { <elements> } */
        ;

base_types:
        INT                     { sentence_set_type(&current, INT_L); }
        | LONG                  { sentence_set_type(&current, LONG_L); }
        | LONG INT              { sentence_set_type(&current, LONG_L); }
        | LONG LONG             { sentence_set_type(&current, LONG_LONG_L); }
        | UNSIGNED              { sentence_set_type(&current, UINT_L); }
        | UNSIGNED INT          { sentence_set_type(&current, UINT_L); }
        | UNSIGNED LONG         { sentence_set_type(&current, ULONG_L); }
        ;

struct_definition:
        STRUCT_DEC optionaly_name '{' elements_declaration '}' {
                apply_user_type(STRUCT_L);
                }
        ;

union_definition:
        UNION_DEC optionaly_name '{' elements_declaration '}' {
                apply_user_type(UNION_L);
                }
        ;

optionaly_name: /* it' not mandatory */ { add_user_type(0); }
        | WORD { add_user_type($1); }
        ;

elements_declaration: /* empty elements list */
        | elements_declaration declaration_op
        ;
%%
