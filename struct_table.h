#ifndef STRUCT_TABLE_DEF
#define STRUCT_TABLE_DEF

extern "C"
{
#include "declaration.h"

void struct_table_init(void);
void show_variable_table();
void show_types_table();
void show_typedefs_table(void);

void add_variable(declaration_t* declaration);
void apply_user_type(unsigned ltype);

void add_user_type(declaration_t* declaration);

void finish_user_type_set_name(const char* name);
void finish_user_type(void);
void finish_user_type_from_table(void);
void add_element(declaration_t* declaration);

void* find_typedef(char*);
}

#endif