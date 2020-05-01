#include <sstream>
#include <cmath>
#include <iostream>

#include "FormulaCell.h"

void FormulaCell::print(std::ostream &stream) 
{ 
    length = 3;
    std::stringstream ss(expression);
    ss.get(); // ignore = sign

    double result = calculate(ss);
    if(valid) stream << result;
    else stream << "ERROR";
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

        number = (*table)[row][col]->getValue();
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
        else
            result /= number;
    }
    return result;
}

double FormulaCell::calculate(std::stringstream &ss)
{
    char ch;

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

    
    return 0;
}

double FormulaCell::getValue()
{
    std::stringstream ss(expression);
    ss.get(); // ignore = sign

    return calculate(ss);
}