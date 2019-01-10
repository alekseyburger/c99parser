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

\n                      /* игнорируем символ конца строки */;
[ \t]+                  /* игнорируем пробелы и символы табуляции */;

.                       return (int) yytext[0];
%%
