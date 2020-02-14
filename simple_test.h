/* run: ./c99_parser <./simple_test.h */

int a = 0x0Ul;

struct sentence_ {
    char name;
    unsigned  is_ptr;
  union {
    int  a;
    int  b;
    struct internal_ {
      unsigned long long l;
      float f;
    } d_struct;
    long c;
  } u;
    };
