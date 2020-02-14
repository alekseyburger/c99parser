#include <stdio.h>
#include <string.h>
#include "declaration.h"

#if(1)
#define debug_printf(fmt, ...)
#else
#define debug_printf(fmt, ...) \
        do { fprintf(stderr, "%s:%d:%s(): " fmt, __FILE__,  __LINE__, __func__, __VA_ARGS__); } while (0)
#endif

void declaration_clean (declaration_t* self) {
    debug_printf("%s\n", self->name);
    self->name[0] = '\0';
    self->type = VOID;
    self->is_ptr = false;
    self->qualifier.is_const = 
    self->qualifier.is_volotile =
    self->qualifier.is_long_long =
    self->qualifier.is_unsigned = 
    self->qualifier.is_register =
    self->qualifier.is_static =
    self->qualifier.is_extern = false;

    self->user_type_ptr = NULL;
}

void declaration_set_type (declaration_t* self, unsigned type) {
    debug_printf("%u\n", type);
    if (type == LONG) {
        if (self->type == LONG) {
            self->qualifier.is_long_long = true;
        } else {
            self->type = LONG;
        }
    } else if (type != INT || self->type == VOID) {
        // don't set INT if it accopanied with size spec
        // like (short...)
        self->type = type;
    }
}

void declaration_set_user_type(declaration_t* self, void* void_user_type_ptr)
{
    self->type = TYPEDEF;
    self->user_type_ptr = void_user_type_ptr;
}

void declaration_set_qualifier (declaration_t* self, unsigned qualifier) {
    debug_printf("%u\n", qualifier);
    switch(qualifier) {
    case UNSIGNED:
        self->qualifier.is_unsigned = true;
        // fall over
    case SIGNED:
        if (self->type == VOID) self->type = INT;
        break;
    case CONST:
        self->qualifier.is_const = true;
        break;
    case VOLATILE:
        self->qualifier.is_volotile = true;
        break;
    case REGISTER:
        self->qualifier.is_register = true;
        break;
    case STATIC:
        self->qualifier.is_static = true;
        break;
    case EXTERN:
        self->qualifier.is_extern = true;
        break;
    default:
        printf("set_qualifier error: unexpected qualifier %u\n", qualifier);
        break;
    }
}

void declaration_set_ptr (declaration_t* self) {
    self->is_ptr = true;
}

void declaration_set_name (declaration_t* self, const char* name) {
    debug_printf("%s\n", name);
    strncpy(self->name, name, DECLARATION_NAME_LEN);
}

void declaration_print_char(const char* c) {
    debug_printf("%s\n", c);
}