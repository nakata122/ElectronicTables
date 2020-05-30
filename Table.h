#ifndef _TABLE_H
#define _TABLE_H

#include <vector>
#include <fstream>
#include "Cells.h"


///Represents a class used to work with a table
class Table
{
private:
    std::string fileName; ///<Currently opened file
    std::vector< std::vector<Cell *> > table;
    std::vector< size_t > maxWidth; ///<Maximum width for each row
    size_t maxCols, maxRows;

    Cell *parse(std::string &str); ///<Returns a new created Cell. 
    void serialize(const std::string &path); ///<Save table in file
public:
    ///Initialize an empty table
    Table(): maxRows(0), maxCols(0) {};
    ~Table(); ///<Clear table contents
    void read(const std::string &path); ///<Open file and load into memory
    void edit(size_t row, size_t col, std::string data); ///<Edits value of a cell with the data which could be any type
    void close(); ///<Closes currently opened file
    void help(); ///<Prints all functions supported by table class
    void save(); ///<Save the currently opened file
    void saveAs(const std::string &path); ///<Save file into a new location

    friend std::ostream &operator <<(std::ostream &stream, Table &obj); ///<Print table contents
};

#endif