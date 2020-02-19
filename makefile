c99parser: lex.yy.o c99_parser.cc struct_table.cpp struct_table.h declaration.o variable.o user_type.o type_def.o struct_lib.o
	g++ --std=c++11 lex.yy.o struct_lib.o variable.o user_type.o type_def.o c99_parser.cc struct_table.cpp declaration.o -o c99parser

lex.yy.o: c99_parser.l y.tab.h
	yacc -d -o c99_parser.cc  c99_parser.y
	lex c99_parser.l
	cc -c lex.yy.c -o lex.yy.o

y.tab.h:  c99_parser.y
	yacc -d c99_parser.y

struct_parser.cc: c99_parser.y declaration.h
	yacc -d -o c99_parser.cc  c99_parser.y

variable.o: variable.h variable.cpp
	g++ --std=c++11  -c variable.cpp

user_type.o: user_type.h user_type.cpp
	g++ --std=c++11  -c user_type.cpp

type_def.o: type_def.h type_def.cpp
	g++ --std=c++11  -c type_def.cpp

struct_lib.o: struct_lib.h struct_lib.cpp
	g++ --std=c++11  -c struct_lib.cpp

declaration.o: declaration.c declaration.h 
	gcc -c declaration.c