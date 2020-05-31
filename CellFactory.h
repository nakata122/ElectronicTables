#ifndef _CELLFACTORY_H
#define _CELLFACTORY_H

#include <string>
#include "Cells.h"
#include "FormulaCell.h"

///Factory class to create new Cell
class CellFactory
{
public:
    static Cell *make(std::string &str, std::vector < std::vector <Cell *> > &_table);
};

#endif