#include "struct_lib.h"

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