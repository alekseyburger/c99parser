/*
*
* Aleksey Burger  (alekseyburger@gmail.com) 2020
* License: BSD
*/

#include <iostream>
#include <string>
#include <vector>
#include <list>

#include "declaration.h"

// get lexem code fom folowing
#include "c99_parser.h"

#ifndef _TYPE_DEF_
#define _TYPE_DEF_

class user_type;

class type_def {
protected:
   unsigned ltype;
   std::string  name;
   type_qualifier_t qualifier;
   user_type* user_type_ptr;       // pointer to struct/union if ltype STRUCT/UNION 
   type_def*  type_def_ptr;        // pointer to parent typedef if ltype TYPEDEF 
public:
   type_def(declaration_t& declaration)
   {
      ltype = declaration.type;
      name = declaration.name;
      qualifier = declaration.qualifier;

      if (ltype == STRUCT || ltype == UNION) {
         user_type_ptr = reinterpret_cast<user_type*>(declaration.user_type_ptr);
      } else if (ltype == TYPEDEF) {
         type_def_ptr = reinterpret_cast<type_def*>(declaration.user_type_ptr);
      }
   };

   std::string to_string(void) const;
   std::string to_short_string(void) const;

   friend std::ostream& operator<<(std::ostream& stream, 
                     const type_def& node) {
      return stream << node.to_string();
   };
};
#endif