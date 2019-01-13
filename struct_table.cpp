#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <algorithm> 
#include <iterator>

#include "struct_table.h"

class variable {

private:
   enum lextype ltype;
   std::string  name;
   std::string  type_name;
public:
   variable(enum lextype ltype, const char* name) :
      ltype(ltype),
      name(name) {
   };
   variable(const char* tname) :
      ltype(NONE_L),
      type_name(tname ? tname : "")
   {};

   void type_define(enum lextype nltype) {
      if (ltype != NONE_L) {
         std::cout << "type_define error" << "\n";
         return;
      }
      ltype = nltype;
   }

   void subtype_define(variable* subtype) {
      type_name = subtype->type_name;
   }

   std::string& get_type_name(void)
   {
      return type_name;
   }

   friend std::ostream& operator<<(std::ostream& stream, 
                     const variable& node) {
      std::string text;
      switch (node.ltype) { 
      case NONE_L: text = "wrong"; break;
      case INT_L: text = "int"; break;
      case UINT_L: text = "unsigned int"; break;
      case LONG_L: text = "long"; break;
      case ULONG_L: text = "unsigned long"; break;
      case LONG_LONG_L: text = "long"; break;
      case ULONG_LONG_L: text = "unsigned long long"; break;
      case STRUCT_L: text.append(std::string("struct "));
         if (node.type_name.length()) text.append(node.type_name);
         else { std::string s = std::to_string(reinterpret_cast<size_t>(&node));
                 text.append("@").append(s); }
         break;
      case UNION_L: text.append(std::string("union "));
         if (node.type_name.length()) text.append(node.type_name);
         else { std::string s = std::to_string(reinterpret_cast<size_t>(&node));
                 text.append("@").append(s); }
         break;
      }
      stream << text << " " << node.name;
      return stream;
   };
};

std::vector<variable*> user_type_stack;
std::unordered_map<std::string,variable*> variables;
std::unordered_map<std::string,variable*> user_types;

#include <stdio.h>
#include <string.h>

extern "C"
{
extern sentence_t current;
void struct_table_init(void)
{
   sentence_clean(&current);
}

extern void yyerror(const char *str);

void apply_user_type(enum lextype ltype)
{
   
   if (user_type_stack.empty()) {
      std::cout << "apply_user_type error" << "\n";
      return;
   }
   variable *var = user_type_stack.back();
   //user_type_stack.pop_back();
   var->type_define(ltype);
   std::string  utype_name(var->get_type_name());
   user_types.insert({utype_name, var});
}

void add_user_type(char* subtype_name)
{
   variable *var = new variable(subtype_name);
   user_type_stack.push_back(var);
}

void add_variable(sentence_t* sentence) {
   std::string name(sentence->name);

   // check the name unique
   if (variables.find(name) != variables.end()) {
      std::cerr << "duplucate varible name " << name << std::endl;
      sentence_clean(sentence);
      return;
   }

   variable *var = new variable(sentence->type, sentence->name);
   if (sentence->type == STRUCT_L || sentence->type == UNION_L) {
      variable *user_type = user_type_stack.back();
      user_type_stack.pop_back();
      var->subtype_define(user_type);
   }
   variables.insert({name,var});

   sentence_clean(sentence);
}

void struct_table_run(void) {
   std::cout << "user_type_stack\n";
   for_each (user_type_stack.begin(),  user_type_stack.end(),  [](variable* p) { std::cout << *p << '\n';} );
   std::cout << "variables\n";
   for_each (variables.begin(),  variables.end(),
         [](std::pair<const std::basic_string<char>, variable*> &p) { std::cout << *p.second << '\n';} );
   std::cout << "user_types\n";
   for_each (user_types.begin(),  user_types.end(),
         [](std::pair<const std::basic_string<char>, variable*> &p) { std::cout << *p.second << '\n';} );
}

}
