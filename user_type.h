#include <iostream>
#include <string>
#include <vector>
#include <list>

extern "C"
{
#include "declaration.h"
}
// get lexem code fom folowing
#include "c99_parser.h"

#ifndef USER_TYPE_DEF
#define USER_TYPE_DEF

class variable;

class user_type {
protected:
   unsigned ltype;
   std::string  name;
   type_qualifier_t qualifier;
   std::vector<variable*> elements;
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
   void insert(variable* element)
   {
      // TBD: check is it composite type
      this->elements.push_back(element);
   };

   void reconstruct_declaration(declaration_t* declaration) const;

   std::string to_string(void) const;
   std::string to_short_string(void) const;

   friend std::ostream& operator<<(std::ostream& stream, 
                     const user_type& node) {
      return stream << node.to_string();
   };
};

class type_def {
protected:
   unsigned ltype;
   std::string  name;
   type_qualifier_t qualifier;
   user_type* user_type_ptr;
   type_def*  type_def_ptr;
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