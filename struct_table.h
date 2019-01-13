extern "C"
{
#include "sentence.h"

void struct_table_init(void);

void add_variable(sentence_t* sentence);
void apply_user_type(enum lextype ltype);
void add_user_type(char*);
void struct_table_run(void);
}
