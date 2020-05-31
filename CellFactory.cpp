
#include "CellFactory.h"

Cell *CellFactory::make(std::string &str, std::vector < std::vector <Cell *> > &_table)
{
    int intNum;
    double doubleNum;
    str = StringHelper::trim(str);

    if(str.size() == 0) return nullptr;

    std::stringstream ss(str);
    if (ss >> intNum && ss.eof()) //Integer
    {   
        return new IntCell(intNum, str.length());
    }
    ss.seekg(0);
    if (ss >> doubleNum && ss.eof()) //Double
    {   
        return new DoubleCell(doubleNum, str.length());
    }
    if(str[0] == '=') //Formula
    {
        return new FormulaCell(str, _table);
    }
    if(str[0] == '"' && str.back() == '"') //String
    {
        std::string result = str.substr(1, str.length() - 2);
        return new StringCell(result, result.length());
    }

    return nullptr;
}