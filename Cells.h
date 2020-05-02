#ifndef _CELLS_H
#define _CELLS_H

#include <fstream>
#include <sstream>
#include <iostream>

#include "StringHelper.cpp"

struct Cell
{
    size_t length;
    Cell(const size_t &_length): length(_length) {};
    virtual void print(std::ostream &stream) = 0;
    virtual void serialize(std::ostream &stream) = 0;
    virtual double getValue() = 0;
};

//Tried with templates first but couldn't make the getValue to work properly for all subclasses

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

class StringCell : public Cell
{
private:
    std::string value;
public:
    StringCell(const std::string &_value, const size_t &_length): Cell(_length), value(_value) {};
    virtual void print(std::ostream &stream) { stream << value;}
    virtual void serialize(std::ostream &stream) { stream << '"' << value << '"';}
    virtual double getValue()
    {
        double result = 0;
        std::string str = StringHelper::trim(value);
        std::stringstream ss(str);

        if (ss >> result && ss.eof()) //Double
        {   
            return result;
        }
        return 0;
    }
};


#endif