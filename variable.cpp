/*
*
* Aleksey Burger (alekseyburger@gmail.com) 2020
* License: BSD
*/

#include <algorithm> 
#include <iterator>
#include <string.h>
#include <unordered_map>

#include "variable.h"
#include "user_type.h"
#include "type_def.h"
#include "struct_lib.h"

std::string variable::to_string(void) const {
      
   std::vector<const char*> type_as_multi_text;

   if (qualifier.is_static) {type_as_multi_text.push_back("static");}
   if (qualifier.is_extern) {type_as_multi_text.push_back("extern");}
   if (qualifier.is_register) {type_as_multi_text.push_back("register");}
   if (qualifier.is_auto) {type_as_multi_text.push_back("auto");}

   if (qualifier.is_const) {type_as_multi_text.push_back("const");}
   if (qualifier.is_volotile) {type_as_multi_text.push_back("volotile");}   
   if (qualifier.is_unsigned) {type_as_multi_text.push_back("unsigned");}
   if (qualifier.is_long_long) {type_as_multi_text.push_back("long");}  
   
   std::string user_type;
   switch (ltype) {
   case STRUCT:
      //type_as_multi_text.push_back("struct");
      user_type = user_type_ptr->to_short_string();
      type_as_multi_text.push_back(user_type.c_str());
      break;
   case UNION:
      //type_as_multi_text.push_back("union");
      user_type = user_type_ptr->to_short_string();
      type_as_multi_text.push_back(user_type.c_str());
      break;
   case TYPEDEF: // it is user defined type
      //type_as_multi_text.push_back("typedef [");
      user_type = type_def_ptr->to_short_string(); 
      type_as_multi_text.push_back(user_type.c_str());
      //type_as_multi_text.push_back("]");
      break;
   default:
      type_as_multi_text.push_back(ltype_to_text(ltype));
      break;
   }
   type_as_multi_text.push_back(name.c_str());

   return string_from_multi_text(type_as_multi_text);
};