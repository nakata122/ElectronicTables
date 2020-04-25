#ifndef _CELLS_H
#define _CELLS_H

#include <fstream>
#include <iostream>

struct Cell
{
    size_t length;
    virtual void print(std::ostream &stream) = 0;
};

template<class  T>
struct TypedCell : public Cell
{
private:
    T value;
public:
    TypedCell(T &_value): value(_value) {};
    virtual void print(std::ostream &stream) { stream << value;}
};
#endif