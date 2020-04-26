#ifndef _CELLS_H
#define _CELLS_H

#include <fstream>
#include <iostream>

struct Cell
{
    size_t length;
    Cell(const size_t &_length): length(_length) {};
    virtual void print(std::ostream &stream) const = 0;
};

template<class  T>
struct TypedCell : public Cell
{
private:
    T value;
public:
    TypedCell(const T &_value, const size_t &_length): Cell(_length), value(_value) {};
    virtual void print(std::ostream &stream) const { stream << value;}
};
#endif