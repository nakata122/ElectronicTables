#ifndef _TABLE_H
#define _TABLE_H

#include <vector>
#include <fstream>
#include "Cells.h"

class Table
{
private:
    std::vector< std::vector<Cell *> > data;
    std::vector< size_t > maxWidth;
public:
    void read(const std::string &path);
    void close();
    void help();

    friend std::ostream &operator <<(std::ostream &stream, Table &obj);
};

#endif