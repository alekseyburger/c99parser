/*
  (C) Aleksey Burger
  c99 lexems definition
*/

%{
#include "y.tab.h"

extern YYSTYPE yylval;

%}

%%
auto        return AUTO; /* Reserved words */
break       return BREAK;
case        return CASE;
char        return CHAR;
const       return CONST;
continue    return CONTINUE;
default     return DEFAULT;
do          return DO;
double      return DOUBLE;
else        return ELSE;
enum        return ENUM;
extern      return EXTERN;
float       return FLOAT;
for         return FOR;
goto        return GOTO;
if          return IF;
int         return INT;
long        return LONG;
register    return REGISTER;
return      return RETURN;
short       return SHORT;
signed      return SIGNED;
sizeof      return SIZEOF;
static      return STATIC;
struct      return STRUCT;
switch      return SWITCH;
typedef     return TYPEDEF;
union       return UNION;
unsigned    return UNSIGNED;
void        return VOID;
volatile    return VOLATILE;
while       return WHILE;

[a-zA-Z][a-zA-Z0-9_]*    strncpy(yylval.str, yytext,ID_MAME_LEN); return ID;  /* identifier */

(0x)?[0-9]+([uU]|[lL]|[uU][lL]|[lL][uU])?  return ICONST;    /* integer literal */

\+    return PLUS;  // Operators
\-   return MINUS;
\*    return TIMES;
\/   return DIVIDE;
\%   return MOD;
\|    return OR;
&    return AND;
~    return NOT;
\^    return XOR;
\<\<   return LSHIFT;
\>\>    return RSHIFT;
\|\|   return LOR;
&&   return LAND;
!    return LNOT;
\<    return LT;
\>    return GT;
\<=    return LE;
\>=   return GE;
==    return EQ;
!=    return NE;

\( return LPAREN; // Delimeters
\) return RPAREN;
\[ return LBRACKET;
\] return RBRACKET;
\{ return LBRACE;
\} return RBRACE;
, return COMMA;
\. return PERIOD;
; return SEMI;
: return COLON;

= return EQUALS;

\/\/[\40-\176]*\n       /* ignore inline comment */
\/\*[\01-\176]*\*\/     /* skip the multiline commment */
\n                      /* ignore new line symbol */;
[ \t]+                  /* ignore blank and tabulation */;

.                       return (int) yytext[0];
%%

/*
    # Literals (identifier, integer constant, float constant, string constant,
    # char const)

# Integer literal
t_ICONST = r'\d+([uU]|[lL]|[uU][lL]|[lL][uU])?'

# Floating literal
t_FCONST = r'((\d+)(\.\d+)(e(\+|-)?(\d+))? | (\d+)e(\+|-)?(\d+))([lL]|[fF])?'

# String literal
t_SCONST = r'\"([^\\\n]|(\\.))*?\"'

# Character constant 'c' or L'c'
t_CCONST = r'(L)?\'([^\\\n]|(\\.))*?\''  
    'TYPEID', 
    'ICONST', 
    'FCONST', 
    'SCONST', 
    'CCONST',

    # Assignment (=, *=, /=, %=, +=, -=, <<=, >>=, &=, ^=, |=)
    'EQUALS', 'TIMESEQUAL', 'DIVEQUAL', 'MODEQUAL', 'PLUSEQUAL', 'MINUSEQUAL',
    'LSHIFTEQUAL', 'RSHIFTEQUAL', 'ANDEQUAL', 'XOREQUAL', 'OREQUAL',

    # Increment/decrement (++,--)
    'PLUSPLUS', 'MINUSMINUS',

    # Structure dereference (->)
    'ARROW',

    # Conditional operator (?)
    'CONDOP',



    # Ellipsis (...)
    'ELLIPSIS',
)

# Completely ignored characters
t_ignore = ' \t\x0c'

# Newlines


def t_NEWLINE(t):
    r'\n+'
    t.lexer.lineno += t.value.count("\n")



# Assignment operators

t_EQUALS = r'='
t_TIMESEQUAL = r'\*='
t_DIVEQUAL = r'/='
t_MODEQUAL = r'%='
t_PLUSEQUAL = r'\+='
t_MINUSEQUAL = r'-='
t_LSHIFTEQUAL = r'<<='
t_RSHIFTEQUAL = r'>>='
t_ANDEQUAL = r'&='
t_OREQUAL = r'\|='
t_XOREQUAL = r'\^='

# Increment/decrement
t_PLUSPLUS = r'\+\+'
t_MINUSMINUS = r'--'

# ->
t_ARROW = r'->'

# ?
t_CONDOP = r'\?'

# Delimeters
t_LPAREN = r'\('
t_RPAREN = r'\)'
t_LBRACKET = r'\['
t_RBRACKET = r'\]'
t_LBRACE = r'\{'
t_RBRACE = r'\}'
t_COMMA = r','
t_PERIOD = r'\.'
t_SEMI = r';'
t_COLON = r':'
t_ELLIPSIS = r'\.\.\.'

# Identifiers and reserved words

reserved_map = {}
for r in reserved:
    reserved_map[r.lower()] = r




# Comments


def t_comment(t):
    r'/\*(.|\n)*?\/'ABURGER
    t.lexer.lineno += t.value.count('\n')

# Preprocessor directive (ignored)


def t_preprocessor(t):
    r'\#(.)*?\n'
    t.lexer.lineno += 1


def t_error(t):
    print("Illegal character %s" % repr(t.value[0]))
    t.lexer.skip(1)

lexer = lex.lex()
if __name__ == "__main__":
    lex.runmain(lexer)
*/