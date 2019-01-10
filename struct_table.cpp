#include <iostream>
#include <string>
#include <vector>

class def_node {
public:
   enum types {NODEF, STRUCT};
private:
   enum types  type;
   std::string name;

public:
   def_node(enum types  type, const char* name) :
      type(type),
      name(name) {
   };

   friend std::ostream& operator<<(std::ostream& stream, 
                     const def_node& node) {
      stream << "struct " << node.name << " ";
      return stream;
   };
};

std::vector<def_node*> defs;

#include <stdio.h>
#include <string.h>

#include "struct_table.h"

extern "C"
{
   void struct_table_init(void) {}


   
   void struct_table_int(const char* name) {
      def_node* node = new def_node(def_node::STRUCT, name);
      defs.push_back(node);
   }
   void struct_table_uint(const char* name) {
      def_node* node = new def_node(def_node::STRUCT, name);
      defs.push_back(node);
   }
    void struct_table_long(const char* name) {
      def_node* node = new def_node(def_node::STRUCT, name);
      defs.push_back(node);
   }
    void struct_table_ulong(const char* name) {
      def_node* node = new def_node(def_node::STRUCT, name);
      defs.push_back(node);
   }
   void struct_table_long_long(const char* name) {
      def_node* node = new def_node(def_node::STRUCT, name);
      defs.push_back(node);
   }
   void struct_table_ulong_long(const char* name) {
      def_node* node = new def_node(def_node::STRUCT, name);
      defs.push_back(node);
   }   
   void struct_table_struct(const char* name) {
      def_node* node = new def_node(def_node::STRUCT, name);
      defs.push_back(node);
   }
      void struct_table_int_ptr(const char* name) {
      def_node* node = new def_node(def_node::STRUCT, name);
      defs.push_back(node);
   }
   void struct_table_uint_ptr(const char* name) {
      def_node* node = new def_node(def_node::STRUCT, name);
      defs.push_back(node);
   }
    void struct_table_long_ptr(const char* name) {
      def_node* node = new def_node(def_node::STRUCT, name);
      defs.push_back(node);
   }
    void struct_table_ulong_ptr(const char* name) {
      def_node* node = new def_node(def_node::STRUCT, name);
      defs.push_back(node);
   }
   void struct_table_long_long_ptr(const char* name) {
      def_node* node = new def_node(def_node::STRUCT, name);
      defs.push_back(node);
   }
   void struct_table_ulong_long_ptr(const char* name) {
      def_node* node = new def_node(def_node::STRUCT, name);
      defs.push_back(node);
   }   
   void struct_table_struct_ptr(const char* name) {
      def_node* node = new def_node(def_node::STRUCT, name);
      defs.push_back(node);
   }
extern void yyerror(const char *str);

void def_user_type(sentence_t* sentence) {}
void def_user_type_end(sentence_t* sentence) {}

void def_variable(sentence_t* sentence) {
        switch (sentence->type) {
        case INT_L:
                if (!sentence->is_ptr) {struct_table_int(sentence->name);}
                else {struct_table_int_ptr(sentence->name);}
                break;
        case UINT_L:
                if (!sentence->is_ptr) {struct_table_uint(sentence->name);}
                else {struct_table_uint_ptr(sentence->name);}
                break;
        case LONG_L:
                if (!sentence->is_ptr) {struct_table_long(sentence->name);}
                else {struct_table_long_ptr(sentence->name);}
                break;
        case ULONG_L:
                if (!sentence->is_ptr) {struct_table_ulong(sentence->name);}
                else {struct_table_ulong_ptr(sentence->name);}
                break;
        case LONG_LONG_L:
                if (!sentence->is_ptr) {struct_table_long_long(sentence->name);}
                else {struct_table_long_long_ptr(sentence->name);}
                break;
        case ULONG_LONG_L:
                if (!sentence->is_ptr) {struct_table_ulong_long(sentence->name);}
                else {struct_table_ulong_long_ptr(sentence->name);}
                break;
        case STRUCT_L:
                if (!sentence->is_ptr) {struct_table_struct(sentence->name ? sentence->name : "n/a");}
                else {struct_table_struct_ptr(sentence->name ? sentence->name : "n/a");}
                break;
        case NONE_L:
                yyerror("error: type is not defined\n");
                break;
        default:
                yyerror("error: type is not expected\n");
                break;
        }
       sentence_clean(sentence);
}


   void struct_table_run(void) {
      for(auto node: defs) {
         std::cout << *node << '\n';
      }
  }
}
