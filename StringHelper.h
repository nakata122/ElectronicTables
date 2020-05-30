#ifndef _STRINGHELPER_H
#define _STRINGHELPER_H

#include<string>
#include<queue>

///Represents a class to extend the functionality of stl string
class StringHelper
{
private:
    static std::queue<std::string> comments; ///<Represents queue, holding comments
public:
    static void addComment(const std::string &comment);///<Add a comment to the queue
    static void printComments();///<Clears queue of comments
    static std::string trim(const std::string &str);///<Removes leading and ending spaces from a string
};

#endif