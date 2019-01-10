struct_parser: lex.yy.o struct_parser.cc struct_table.cpp struct_table.h sentence.o
	g++ --std=c++11 lex.yy.o sentence.o struct_parser.cc sentence.c struct_table.cpp -o struct_parser

lex.yy.o: struct_parser.l y.tab.h
	yacc -d -o struct_parser.cc  struct_parser.y
	lex struct_parser.l
	cc -c lex.yy.c -o lex.yy.o

y.tab.h:  struct_parser.y
	yacc -d struct_parser.y

struct_parser.cc: struct_parser.y sentence.h
	yacc -d -o struct_parser.cc  struct_parser.y

sentence.o: sentence.c sentence.h 
	gcc -c sentence.c -o sentence.o