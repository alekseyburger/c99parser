
#include <algorithm> 
#include <iterator>
#include <map>
#include <unordered_map>

#include "variable.h"
#include "user_type.h"

#include "struct_table.h"


std::vector<user_type*> user_type_stack;

std::unordered_map<std::string,variable*> variables;
std::unordered_map<std::string,user_type*> user_types;
std::map<std::string,type_def*> typedefs;

//#include <stdio.h>

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

void add_user_type(declaration_t* declaration)
{
   user_type *type = new user_type(*declaration);
   user_type_stack.push_back(type);

   if (IS_DEBUG) std::cout << "add_user_type: " << *type << std::endl;

   declaration_clean(declaration);
}

void finish_user_type_set_name(const char* name)
{
   // TBD: check is empty
   user_type *type = user_type_stack.back();
   type->set_name(name);

   if (IS_DEBUG) std::cout << "finish_user_type_set_name: " << *type << std::endl;

   user_type_stack.pop_back();

   user_types.insert({type->get_name(), type});

   type->reconstruct_declaration(&current);
   //declaration_set_user_type(&current, (void*)type);
}

void finish_user_type(void)
{
   // TBD: check is empty
   user_type *type = user_type_stack.back();
   user_type_stack.pop_back();

   if (IS_DEBUG) std::cout << "finish_user_type: " << *type << std::endl;

   // insert user struct/union in user_types table
   user_types.insert({type->get_name(), type});

   // reset current declaration as struct/union
   type->reconstruct_declaration(&current);
   //declaration_set_user_type(&current, (void*)type);
}

void finish_user_type_from_table(void)
{
   // TBD: check is empty
   user_type *type = user_type_stack.back();
   user_type_stack.pop_back();

   type->reconstruct_declaration(&current);
   if (IS_DEBUG) std::cout << "finish_user_type_from_table: " << type->get_name() << std::endl;
}

void add_element(declaration_t* declaration) {
   std::string name(declaration->name);

   // TBD: check is empty
   if (user_type_stack.empty()){
      std::cerr << "add element: user_type_stack is empty" << std::endl;
      declaration_clean(declaration);
      return;
   }

   user_type *composit_type = user_type_stack.back();

   variable *var = new variable(*declaration);
   composit_type->insert(var);
   if (IS_DEBUG) std::cout << "add_element: " << *var << std::endl;

   // clean current element declaration
   declaration_clean(declaration);
}

void add_variable(declaration_t* declaration) {
   std::string name(declaration->name);

   if (declaration->qualifier.is_typedef){
      //if (IS_DEBUG) std::cout << "add typedef: " << name << " as: " << declaration_to_string(declaration)  << std::endl;
      type_def *type_ptr = new type_def(*declaration);

      typedefs.insert({name, type_ptr});
      if (IS_DEBUG) std::cout << "add typedef: " << name << " as: " <<  *type_ptr << std::endl;
      declaration_clean(declaration);
      return;
   }

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

/*
* try to find name_c in user_types table as typedef. If found return
* pointer to type. Otherwise NULL;
*/
void* find_typedef(char* name_c){
   std::string name(name_c);

   // std::unordered_map<std::string,user_type*>::iterator 
   auto iter = typedefs.find(name);
   if (iter  != typedefs.end()) {
      if (IS_DEBUG) std::cout << "found typedef name: " << name  << std::endl;
      return (void*) &(*iter->second);
   }
   if (IS_DEBUG) std::cout << "NOT found typedef name: " << name << std::endl;
   return NULL;
}

void show_variable_table(void) {

   std::cout << "variables:\n";
   for_each (variables.begin(),  variables.end(),
         [](std::pair<const std::basic_string<char>, variable*> &p) { std::cout << '\t' << *p.second << '\n';} );
}

void show_types_table(void) {
   std::cout << "user_types:\n";
   for_each (user_types.begin(),  user_types.end(),
         [](std::pair<const std::basic_string<char>, user_type*> &p) { 
            std::cout << '\t' << *p.second << '\n';} );
}

void show_typedefs_table(void) {
   std::cout << "typedefs:\n";
   for_each (typedefs.begin(),  typedefs.end(),
         [](std::pair<const std::basic_string<char>, type_def*> &p) { 
            std::cout << '\t' << p.first << ": " << *p.second << '\n';} );
}
} // extern "C"
