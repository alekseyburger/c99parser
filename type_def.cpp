/*
*
* Aleksey Burger (alekseyburger@gmail.com) 2020
* License: BSD
*/

#include <algorithm> 

#include "type_def.h"
#include "user_type.h"
#include "struct_lib.h"


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