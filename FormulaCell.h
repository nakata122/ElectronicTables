#ifndef _FORMULA_H
#define _FORMULA_H

#include <string>
#include <vector>

#include "Cells.h"

///Cell containing formula
/*!
 * Calculates the value of a formula.
 * Works with references to other cells and multiple parameters */
class FormulaCell: public Cell
{
private:
    std::vector < std::vector <Cell *> > &table;
    std::string expression;
    bool valid = true;

    double getNum(std::stringstream &str); ///<Get single formatted number
    double firstPriority(std::stringstream &str); ///<Power of number
    double secondPriority(std::stringstream &str); ///<Multiply and divide until possible
    double calculate(std::stringstream &str); ///<Sum and substract until possible. Works with more than 2 parameters
public:
    ///Initialize the formula cell with a reference to a table and some expression to be calculated
    FormulaCell(const std::string &_expression, std::vector < std::vector <Cell *> > &_table): Cell(0), expression(_expression), table(_table) {};
    virtual Cell *clone(std::vector < std::vector <Cell *> > &_table);
    virtual void print(std::ostream &stream);
    virtual void serialize(std::ostream &stream);
    virtual double getValue();
};

#endif