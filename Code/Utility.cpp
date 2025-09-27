#include "Utility.h"

int string_to_int(const std::string& s){
   std::istringstream ss(s);
   int n;
   ss >> n;
   return n;
}

bool isNumber(const std::string& str)
{
    for (char const &c : str) {
        if (std::isdigit(c) == 0) return false;
    }
    return !str.empty();
}

bool isUpperLetter(const std::string& str) {
    return str.size() == 1 && isupper(str[0]);
}