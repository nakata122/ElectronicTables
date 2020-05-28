#ifndef _STRINGHELPER_H
#define _STRINGHELPER_H

#include<string>
#include<queue>

struct StringHelper
{
private:
    static std::queue<std::string> comments;
public:
    static void addComment(const std::string &comment);
    static void printComments();
    static std::string trim(const std::string &str);
};

#endif