extern "C"
{
#include "declaration.h"

void struct_table_init(void);
void struct_table_run(void);

void add_variable(declaration_t* declaration);
void apply_user_type(unsigned ltype);

void add_user_type(unsigned ltype);
//void add_user_type(unsigned ltype, char*);
void finish_user_type_set_name(const char* name);
void finish_user_type(void);
void finish_user_type_from_table(void);
void add_element(declaration_t* declaration);

}
