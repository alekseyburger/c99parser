#include "sentence.h"

void sentence_clean (sentence_t* self) {
        self->name = 0;
        self->type = NONE_L;
        self->is_ptr = false;       
}

void sentence_set_type (sentence_t* self, enum lextype type) {
    self->type = type;
}

void sentence_set_ptr (sentence_t* self) {
    self->is_ptr = true;
}

void sentence_set_name (sentence_t* self, const char* name) {
    self->name = name;
}