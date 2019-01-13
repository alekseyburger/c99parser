%{
#include "y.tab.h"

extern YYSTYPE yylval;

%}


%%
[0-9]+                  return NUMBER;

int                     return INT;
long                    return LONG;
unsigned                return UNSIGNED;

struct                  return STRUCT_DEC;
union                   return UNION_DEC;

[a-zA-Z][a-zA-Z0-9_]*    yylval.strptr = yytext; return WORD;

\/\/[\40-\176]*\n       /* ignore inline comment */
\/\*[\01-\176]*\*\/     /* skip the multiline commment */
\n                      /* ignore new line symbol */;
[ \t]+                  /* ignore blank and tabulation */;

.                       return (int) yytext[0];
%%
