#ifndef DECLARATION_DEF
#define DECLARATION_DEF

#define false 0
#define true (!false)

typedef struct type_qualifier_ {
    int is_typedef:1;
    int is_const:1;
    int is_volotile:1;
    int is_long_long:1;     
    int is_unsigned:1;
    int is_register:1;
    int is_static:1;
    int is_extern:1;
} type_qualifier_t;

void qualifier_clean (type_qualifier_t* self);

#define DECLARATION_NAME_LEN  256
struct declaration_ {
    char name[DECLARATION_NAME_LEN];
    unsigned  type;
    int  is_ptr;
    type_qualifier_t qualifier;
    void*  user_type_ptr;
};

typedef struct declaration_ declaration_t;

void declaration_clean (declaration_t* self);
void declaration_set_type (declaration_t* self, unsigned  type);
void declaration_set_user_type(declaration_t* self, void* void_user_type_ptr);
void declaration_set_qualifier (declaration_t* self, unsigned qualifier);
void declaration_set_ptr (declaration_t* self); 
void declaration_set_name (declaration_t* self, const char* name);

void declaration_print_char(const char* c);

const char* ltype_to_text(unsigned ltype);
#endif