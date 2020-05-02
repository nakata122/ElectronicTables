#ifndef _TABLE_H
#define _TABLE_H

#include <vector>
#include <fstream>
#include "Cells.h"

class Table
{
private:
    std::string fileName;
    std::vector< std::vector<Cell *> > table;
    std::vector< size_t > maxWidth;
    size_t maxCols, maxRows;

    Cell *parse(std::string &str);
    void serialize(const std::string &path);
public:
    Table(): maxRows(0), maxCols(0) {};
    ~Table();
    void read(const std::string &path);
    void edit();
    void close();
    void help();
    void save();
    void saveAs(const std::string &path);

    friend std::ostream &operator <<(std::ostream &stream, Table &obj);
};

#endif