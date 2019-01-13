#define false 0
#define true (!false)

enum lextype {
      NONE_L=0,
      INT_L,
      UINT_L,
      LONG_L,
      ULONG_L,
      LONG_LONG_L,
      ULONG_LONG_L,
      STRUCT_L,
      UNION_L
     };

struct sentence_ {
    const char* name;
    enum lextype type;
    unsigned  is_ptr;  
};

typedef struct sentence_ sentence_t;


void sentence_clean (sentence_t* self);
void sentence_set_type (sentence_t* self, enum lextype type); 
void sentence_set_ptr (sentence_t* self); 
void sentence_set_name (sentence_t* self, const char* name);