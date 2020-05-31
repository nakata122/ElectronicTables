#include <sstream>
#include <cmath>
#include <string> 
#include <iostream>

#include "FormulaCell.h"

void FormulaCell::serialize(std::ostream &stream) 
{ 
    stream << expression;
}

Cell *FormulaCell::clone(std::vector < std::vector <Cell *> > &_table)
{
    return new FormulaCell(expression, _table);
}

void FormulaCell::print(std::ostream &stream) 
{ 
    length = 3;
    std::stringstream ss(expression);
    ss.get(); // ignore = sign

    double result = calculate(ss);
    if(valid) {
        std::ostringstream checkSize;
        checkSize << result;
        length = checkSize.tellp();
        checkSize.clear();

        stream << result;
    }
    else 
    {
        length = 5;
        stream << "ERROR";
    }
}

double FormulaCell::getNum(std::stringstream &ss)
{
    double number;
    char ch;

    while (ss.peek() == ' ') ss.get(); // Skip spaces

    std::streampos pos = ss.tellg();

    if(!(ss >> number)) // Reference found
    {
        size_t row = 0, col = 0;

        ss.clear();
        ss.seekg(pos);
        ss.get(ch);
        if(ch == 'R') ss >> row;
        else return 0;

        ss.get(ch);
        if(ch == 'C') ss >> col;
        else return 0;

        if(row >= table.size() || col >= table[row].size()) 
        {
            StringHelper::addComment("Element at row " + std::to_string(row) + " col " + std::to_string(col) + " does not exits\n");
            number = 0;
        }
        else if(table[row][col] == nullptr)
        {
            StringHelper::addComment("Element at row " + std::to_string(row) + " col " + std::to_string(col) + " is empty\n");
            number = 0;
        }
        else if(table[row][col] == this)
        {
            StringHelper::addComment("Element at row " + std::to_string(row) + " col " + std::to_string(col) + " contains recursive definition\n");
            number = 0;
        }
        else
            number = table[row][col]->getValue();
    }

    while (ss.peek() == ' ') ss.get(); // Skip spaces

    return number;
}

double FormulaCell::firstPriority(std::stringstream &ss)
{   
    char ch;
    double result = getNum(ss);
    while(ss.peek() == '^')
    {
        ss.get(ch);
        double number = getNum(ss);

        result = pow(result, number);
    }

    return result;
}

double FormulaCell::secondPriority(std::stringstream &ss)
{
    char ch;
    double result = firstPriority(ss);
    while (ss.peek() == '*' || ss.peek() == '/')
    {
        ss.get(ch);
        double number = firstPriority(ss);

        if (ch == '*')
            result *= number;
        else if(number == 0 && ch == '/')
        {
            valid = false;
            return 0;
        }
        else
            result /= number;
    }
    return result;
}

double FormulaCell::calculate(std::stringstream &ss)
{
    char ch;
    valid = true;

    double result = secondPriority(ss);
    while (ss.peek() == '+' || ss.peek() == '-')
    {
        ss.get(ch);

        if (ch == '+')
            result += secondPriority(ss);
        else
            result -= secondPriority(ss);
    }
    return result;
}

double FormulaCell::getValue()
{
    std::stringstream ss(expression);
    ss.get(); // ignore = sign

    return calculate(ss);
}