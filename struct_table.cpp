#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <algorithm> 
#include <iterator>

#include "struct_table.h"

class user_type;

class variable {
private:
   unsigned ltype;
   std::string  name;
   type_qualifier_t qualifier;
   user_type* user_type_ptr;
public:
   variable(declaration_t& declaration) :
      ltype {declaration.type},
      name {declaration.name},
      user_type_ptr {reinterpret_cast<user_type*>(declaration.user_type_ptr)}
   {
      qualifier = declaration.qualifier;
   };

   variable(const char* tname) :
      ltype(VOID)
   {};

   std::string to_string(void) const;

   friend std::ostream& operator<<(std::ostream& stream, 
                     const variable& node) {

      stream << node.to_string();
      return stream;
   };
};

class user_type {
private:
   unsigned ltype;
   std::string  name;
   std::unordered_map<std::string,variable*> elements;
public:
   user_type(unsigned ltype) :
      ltype(ltype)
   {
      char  name_buf[DECLARATION_NAME_LEN];
      snprintf(name_buf, DECLARATION_NAME_LEN, "@%p", this);
      name = name_buf;
   };

   user_type(unsigned ltype, const char* name) :
      ltype(ltype),
      name(name)
   {
   };

   const std::string& get_name(void) const {return name;};
   void set_name(const char* newname) 
   {
      name = newname;
   };

   // add new elemet to composite type
   void insert(const std::pair<std::string, variable*> &element)
   {
      // TBD: check is it composite type
      auto res = elements.insert(element);
      if (!res.second) {
         std::cerr << "duplucate element name " << element.first 
         << "can't be added to "
         << name
         << std::endl;
      }
   };

   std::string to_string(void) const;
   std::string to_short_string(void) const;

   friend std::ostream& operator<<(std::ostream& stream, 
                     const user_type& node) {
      return stream << node.to_string();
   };
};

std::vector<user_type*> user_type_stack;

std::unordered_map<std::string,variable*> variables;
std::unordered_map<std::string,user_type*> user_types;

std::string string_from_multi_text(std::vector<const char*> &type_as_multi_text)
{
      std::string type_as_text;

      bool is_first = true;
      for(auto &p : type_as_multi_text) {
         if (!is_first) {
            type_as_text += " ";
         }
         is_first = false;
         type_as_text += p;
      }

      return type_as_text;
}

std::string variable::to_string(void) const {
      
   std::vector<const char*> type_as_multi_text;

   if (qualifier.is_static) {type_as_multi_text.push_back("static");}
   if (qualifier.is_extern) {type_as_multi_text.push_back("extern");}
   if (qualifier.is_register) {type_as_multi_text.push_back("register");}

   if (qualifier.is_const) {type_as_multi_text.push_back("const");}
   if (qualifier.is_volotile) {type_as_multi_text.push_back("volotile");}   
   if (qualifier.is_unsigned) {type_as_multi_text.push_back("unsigned");}
   if (qualifier.is_long_long) {type_as_multi_text.push_back("long");}  

   std::string user_type;

   switch (ltype) { 
   case VOID: type_as_multi_text.push_back("void"); break;
   case CHAR: type_as_multi_text.push_back("char"); break;
   case INT: type_as_multi_text.push_back("int"); break;
   case SHORT: type_as_multi_text.push_back("short"); break;
   case LONG: type_as_multi_text.push_back("long"); break;
   case FLOAT: type_as_multi_text.push_back("float"); break;
   case DOUBLE: type_as_multi_text.push_back("double"); break;
   case TYPEDEF: // it is user defined type
      user_type = user_type_ptr->to_short_string();
      type_as_multi_text.push_back(user_type.c_str());
      break;
   default:
      type_as_multi_text.push_back("[unexpected variable type]");
      break;
   }
   type_as_multi_text.push_back(name.c_str());

   return string_from_multi_text(type_as_multi_text);
};

std::string user_type::to_short_string(void) const {

   std::vector<const char*> type_as_multi_text;

   switch (ltype) { 
   case STRUCT: type_as_multi_text.push_back("struct");
      break;
   case UNION: type_as_multi_text.push_back("union");
      break;
   default:
      type_as_multi_text.push_back("[unexpected user type]");
      break;
   }
   
   type_as_multi_text.push_back(name.c_str());
   return string_from_multi_text(type_as_multi_text); 
}

std::string user_type::to_string(void) const {

   std::string type_as_text(to_short_string());
   std::vector<const char*> type_as_multi_text;
   type_as_multi_text.push_back(type_as_text.c_str());

   type_as_multi_text.push_back("{");

   bool is_cont = false;
   std::string elements_as_text;
   for_each (elements.begin(),  elements.end(),
      [&](const std::pair<const std::basic_string<char>, variable*> &p) {
         if (is_cont) { elements_as_text += ","; }
         elements_as_text += p.second->to_string();
         is_cont = true;
      } );
   type_as_multi_text.push_back(elements_as_text.c_str());
   type_as_multi_text.push_back("}");
   return string_from_multi_text(type_as_multi_text);
}

#include <stdio.h>
#include <string.h>

extern "C"
{
extern declaration_t current;
void struct_table_init(void)
{
   declaration_clean(&current);
}

extern void yyerror(const char *str);

const bool IS_DEBUG = false;

/*
   Following functions provide C interface to tables
*/
void apply_user_type(unsigned ltype)
{
   if (user_type_stack.empty()) {
      std::cerr << "apply_user_type error" << "\n";
      return;
   }
}

void add_user_type(unsigned ltype)
{
   user_type *type = new user_type(ltype);
   user_type_stack.push_back(type);

   if (IS_DEBUG) std::cout << "add_user_type: " << type->get_name() << std::endl;
}

void finish_user_type_set_name(const char* name)
{
   // TBD: check is empty
   user_type *type = user_type_stack.back();
   user_type_stack.pop_back();
   type->set_name(name);

   user_types.insert({type->get_name(), type});

   declaration_clean(&current);
   declaration_set_user_type(&current, (void*)type);   
}

void finish_user_type(void)
{
   // TBD: check is empty
   user_type *type = user_type_stack.back();
   user_type_stack.pop_back();

   user_types.insert({type->get_name(), type});

   declaration_clean(&current);
   declaration_set_user_type(&current, (void*)type);
}

void finish_user_type_from_table(void)
{
   // TBD: check is empty
   user_type *type = user_type_stack.back();
   user_type_stack.pop_back();
}

void add_element(declaration_t* declaration) {

   std::string name(declaration->name);
   if (IS_DEBUG) std::cout << "add_element: " << name << std::endl;
   // TBD: check is empty
   if (user_type_stack.empty()){
      std::cerr << "add element: user_type_stack is empty" << std::endl;
      declaration_clean(declaration);
      return;
   }
   user_type *type = user_type_stack.back();

   variable *var = new variable(*declaration);
   type->insert({name,var});

   // clean current element declaration
   declaration_clean(declaration);
}

void add_variable(declaration_t* declaration) {
   std::string name(declaration->name);

   // check the name unique
   if (variables.find(name) != variables.end()) {
      std::cerr << "duplucate varible name " << name << std::endl;
      declaration_clean(declaration);
      return;
   }

   variable *var = new variable(*declaration);
   variables.insert({name,var});

   if (IS_DEBUG) std::cout << "add varible name: " << *var << std::endl;

   declaration_clean(declaration);
}

void struct_table_run(void) {

   std::cout << "variables:\n";
   for_each (variables.begin(),  variables.end(),
         [](std::pair<const std::basic_string<char>, variable*> &p) { std::cout << '\t' << *p.second << '\n';} );
   
   std::cout << "user_types:\n";
   for_each (user_types.begin(),  user_types.end(),
         [](std::pair<const std::basic_string<char>, user_type*> &p) { std::cout << '\t' << *p.second << '\n';} );
}

} // extern "C"
