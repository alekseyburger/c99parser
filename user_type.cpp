#include <algorithm> 
// #include <iterator>

// #include <unordered_map>

#include "variable.h"
#include "user_type.h"
#include <string.h>
#include "struct_lib.h"

void user_type::reconstruct_declaration(declaration_t* declaration) const
{
   declaration_clean(declaration);
   strncpy(declaration->name,name.c_str(),DECLARATION_NAME_LEN);
   declaration->type = ltype;
   //int  is_ptr;
   declaration->qualifier = qualifier;
   //declaration->user_type_ptr = typedef_ptr;
   declaration->user_type_ptr = (void*)this;
}

std::string user_type::to_short_string(void) const {

   std::vector<const char*> type_as_multi_text;
   std::string buf;

   switch (ltype) { 
   case STRUCT: 
      type_as_multi_text.push_back("struct");
      type_as_multi_text.push_back(name.c_str());
      break;
   case UNION: 
      type_as_multi_text.push_back("union");
      type_as_multi_text.push_back(name.c_str());
      break;
   case TYPEDEF: 
      type_as_multi_text.push_back("typedef");
      if (typedef_ptr) {
         buf = typedef_ptr->to_short_string();
         type_as_multi_text.push_back(buf.c_str());
      } else {
         type_as_multi_text.push_back(ltype_to_text(ltype));
      }
      break;
   default:
      buf = ltype_to_text(ltype);
      type_as_multi_text.push_back(buf.c_str());
      break;
   }
   
   return string_from_multi_text(type_as_multi_text); 
}

std::string user_type::to_string(void) const {

   std::string type_as_text(to_short_string());
   std::vector<const char*> type_as_multi_text;
   type_as_multi_text.push_back(type_as_text.c_str());

   std::string elements_as_text;
   if (ltype == STRUCT || ltype == UNION){
      bool is_cont = false;
      elements_as_text += " {";
      for_each (elements.begin(),  elements.end(),
         [&](const variable* p) {
            if (is_cont) { elements_as_text += ","; }
            elements_as_text += p->to_string();
            is_cont = true;
         } );
      elements_as_text += "}";
   }

   return string_from_multi_text(type_as_multi_text) + elements_as_text;
}

std::string type_def::to_short_string(void) const {  

   return name;
}

std::string type_def::to_string(void) const {  

   std::vector<const char*> type_as_multi_text;
   std::string buf;
   if (ltype == STRUCT || ltype == UNION) {
      buf = user_type_ptr->to_short_string();
      type_as_multi_text.push_back(buf.c_str());
   } else if (ltype == TYPEDEF) {
      buf = type_def_ptr->to_short_string();
      type_as_multi_text.push_back(buf.c_str());      
   } else {
      type_as_multi_text.push_back(ltype_to_text(ltype));
   }

   return string_from_multi_text(type_as_multi_text);
}