#ifndef _FORMULA_H
#define _FORMULA_H

#include <string>
#include <vector>

#include "Cells.h"

class FormulaCell: public Cell
{
private:
    std::vector < std::vector <Cell *> > *table;
    std::string expression;
    bool valid = true;

    double getNum(std::stringstream &str); //Get single formatted number
    double firstPriority(std::stringstream &str); //Power of number
    double secondPriority(std::stringstream &str); //Multiply and divide until possible
    double calculate(std::stringstream &str); //Sum and substract until possible. Works with more than 2 parameters
public:
    FormulaCell(const std::string &str, std::vector < std::vector <Cell *> > *_table): Cell(0), expression(str), table(_table) {};
    virtual void print(std::ostream &stream);
    virtual double getValue();
};

#endif