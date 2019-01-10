extern "C"
{
#include "sentence.h"

void struct_table_init(void);

void def_variable(sentence_t* sentence);
void def_user_type(sentence_t* sentence);
void def_user_type_end(sentence_t* sentence);
void struct_table_run(void);
}
