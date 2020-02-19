/*
* Variable properties (parser output)
* 
* Aleksey Burger (alekseyburger@gmail.com) 2020
* License: BSD
*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "declaration.h"
// get lexem code fom folowing
#include "c99_parser.h"

#if(1)
#define debug_printf(fmt, ...)
#else
#define debug_printf(fmt, ...) \
        do { fprintf(stderr, "%s:%d:%s(): " fmt, __FILE__,  __LINE__, __func__, __VA_ARGS__); } while (0)
#endif

void qualifier_clean (type_qualifier_t* self) {
    self->is_typedef =
    self->is_const = 
    self->is_volotile =
    self->is_long_long =
    self->is_unsigned = 
    self->is_register =
    self->is_auto =
    self->is_static =
    self->is_extern = false;
}

void declaration_clean (declaration_t* self) {
    debug_printf("%s\n", self->name);
    self->name[0] = '\0';
    self->type = VOID;
    self->is_ptr = false;
    self->user_type_ptr = NULL;
    qualifier_clean(&self->qualifier);

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

void declaration_set_user_type (declaration_t* self, void* user_type_ptr) {
    self->user_type_ptr = user_type_ptr; // pointer to type_def
}

void declaration_set_qualifier (declaration_t* self, unsigned qualifier) {
    debug_printf("%u\n", qualifier);
    switch(qualifier) {
    case TYPEDEF:
        self->qualifier.is_typedef = true;
        break;
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
    case AUTO:
        self->qualifier.is_auto = true;
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

const char* ltype_to_text(unsigned ltype)
{
   switch (ltype) { 
   case VOID: return "void"; break;
   case CHAR: return("char"); break;
   case INT: return("int"); break;
   case SHORT: return("short"); break;
   case LONG: return("long"); break;
   case FLOAT: return("float"); break;
   case DOUBLE: return("double"); break;
   default:
        {
        static char buf[1024];
        snprintf(buf, 1024, "[unexpected variable type %u]", ltype);
        return (buf);
        }
      break;
   }
}