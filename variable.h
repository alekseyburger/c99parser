/*
*
* Aleksey Burger (alekseyburger@gmail.com) 2020
* License: BSD
*/

#include <iostream>
#include <string>
#include <vector>
#include <list>

#include "declaration.h"

// get lexem code fom folowing
#include "c99_parser.h"

#ifndef VARIABLE_DEF
#define VARIABLE_DEF

class user_type;
class type_def;

class variable {
private:
   unsigned ltype;
   std::string  name;
   type_qualifier_t qualifier;
   user_type* user_type_ptr;
   type_def*  type_def_ptr;
public:

   variable(const declaration_t& declaration) :
      ltype {declaration.type},
      name {declaration.name}
   {
        qualifier = declaration.qualifier;
        if (ltype == STRUCT || ltype == UNION) {
            user_type_ptr = reinterpret_cast<user_type*>(declaration.user_type_ptr);
        } else if (ltype == TYPEDEF) {
            type_def_ptr = reinterpret_cast<type_def*>(declaration.user_type_ptr);
        }
   };

   variable(const char* tname) :
      ltype(VOID)
   {
      qualifier_clean(&qualifier);
   };

   std::string to_string(void) const;

   friend std::ostream& operator<<(std::ostream& stream, 
                     const variable& node) {

      stream << node.to_string();
      return stream;
   };

};
#endif