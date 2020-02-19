/*
*
* Aleksey Burger (alekseyburger@gmail.com) 2020
* License: BSD
*/

#include <iostream>
#include <string>
#include <vector>
#include <list>
#include <memory>

#include "declaration.h"
#include "variable.h"

// get lexem code fom folowing
#include "c99_parser.h"

#ifndef _USER_TYPE_
#define _USER_TYPE_

class variable;

class user_type {
protected:
   unsigned ltype;
   std::string  name;
   type_qualifier_t qualifier;
   std::vector<std::unique_ptr<variable>> elements;
   user_type* typedef_ptr;
public:
   user_type(declaration_t& declaration)
   {
         ltype = declaration.type;
         if (declaration.name[0]) {
            name = declaration.name;
         } else {
            char  name_buf[DECLARATION_NAME_LEN];
            snprintf(name_buf, DECLARATION_NAME_LEN, "@%p", this);
            name = name_buf;           
         }
         qualifier = declaration.qualifier;
         typedef_ptr = reinterpret_cast<user_type*>(declaration.user_type_ptr);
   };

   const std::string& get_name(void) const {return name;};

   void set_name(const char* newname) 
   {
      name = newname;
   };

   const type_qualifier_t* get_qualifier(void) 
   {
      return &qualifier;
   };

   // add new elemet to composite type
   void addElemant(variable* element)
   {
      this->elements.push_back(std::unique_ptr<variable>{element});
   };

   void reconstruct_declaration(declaration_t* declaration) const;
   declaration_t get_declaration(void) const;

   std::string to_string(void) const;
   std::string to_short_string(void) const;

   friend std::ostream& operator<<(std::ostream& stream, 
                     const user_type& node) {
      return stream << node.to_string();
   };
};
#endif