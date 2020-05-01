#ifndef _STRING_HELPER
#define _STRING_HELPER

#include<string>

struct StringHelper
{
    static std::string trim(const std::string &str)
    {
        size_t first = str.find_first_not_of(' ');
        size_t last = str.find_last_not_of(' ');

        size_t width = last - first + 1;

        return str.substr(first, width);
    }
};

#endif