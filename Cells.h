#ifndef _CELLS_H
#define _CELLS_H

#include <fstream>
#include <sstream>
#include <iostream>

#include "StringHelper.h"

/// Abstract class Cell used for holding different value types
class Cell
{
public:
    size_t length; ///<Amount of characters needed to print. Used for alignment when printing
    ///Initialize an empty cell
    Cell(const size_t &_length): length(_length) {}; 
    virtual void print(std::ostream &stream) = 0; ///<Print on console
    virtual void serialize(std::ostream &stream) = 0; ///<Save in file
    virtual double getValue() = 0; ///<Returns a double number for calculating a formula
};

///Cell holding integer values
class IntCell : public Cell
{
private:
    int value;
public:
    IntCell(const int &_value, const size_t &_length): Cell(_length), value(_value) {};
    virtual void print(std::ostream &stream) { stream << value;}
    virtual void serialize(std::ostream &stream) { stream << value;}
    virtual double getValue()
    {
        return (double)value;
    }
};

///Cell holding double values
class DoubleCell : public Cell
{
private:
    double value;
public:
    DoubleCell(const double &_value, const size_t &_length): Cell(_length), value(_value) {};
    virtual void print(std::ostream &stream) { stream << value;}
    virtual void serialize(std::ostream &stream) { stream << value;}
    virtual double getValue()
    {
        return value;
    }
};

///Cell holding string values
class StringCell : public Cell
{
private:
    std::string value;
public:
    StringCell(const std::string &_value, const size_t &_length): Cell(_length), value(_value) {};
    virtual void print(std::ostream &stream) { stream << value;}
    virtual void serialize(std::ostream &stream) { stream << '"' << value << '"';}
    virtual double getValue() ///<Converts string into a double value if possible
    {
        double result = 0;
        std::string str = StringHelper::trim(value);
        std::stringstream ss(str);

        if (ss >> result && ss.eof()) //Double
        {
            StringHelper::addComment("The string \"" + value + "\" is converted to " + value + "\n");
            return result;
        }
        StringHelper::addComment("The string " + value + " is converted to 0\n");
        return 0;
    }
};


#endif