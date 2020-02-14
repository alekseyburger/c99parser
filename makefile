c99_parser: lex.yy.o c99_parser.cc struct_table.cpp struct_table.h declaration.o
	g++ --std=c++11 lex.yy.o declaration.o c99_parser.cc declaration.c struct_table.cpp -o c99_parser

lex.yy.o: c99_parser.l y.tab.h
	yacc -d -o c99_parser.cc  c99_parser.y
	lex c99_parser.l
	cc -c lex.yy.c -o lex.yy.o

y.tab.h:  c99_parser.y
	yacc -d c99_parser.y

struct_parser.cc: c99_parser.y declaration.h
	yacc -d -o c99_parser.cc  c99_parser.y

declaration.o: declaration.c declaration.h 
	gcc -c declaration.c -o declaration.o