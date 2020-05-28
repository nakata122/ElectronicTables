#include <iostream>
#include "StringHelper.h"


std::queue<std::string> StringHelper::comments = std::queue<std::string>();

void StringHelper::addComment(const std::string &comment)
{
    comments.push(comment);
}

void StringHelper::printComments()
{
    while(!comments.empty())
    {
        std::cout << StringHelper::comments.back();
        comments.pop();
    }
}

std::string StringHelper::trim(const std::string &str)
{
    if(str.length() == 0) return str;
    size_t first = 0, last = str.size() - 1;

    while(str[first] == ' ' || str[first] == '\t' || str[first] == '\r' || str[first] == '\n') first++;
    while(str[last] == ' ' || str[last] == '\t' || str[last] == '\r' || str[last] == '\n') last--;

    size_t width = last - first + 1;

    return str.substr(first, width);
}
