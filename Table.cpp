
#include <string>
#include <fstream>
#include <sstream>

#include "StringHelper.cpp"
#include "FormulaCell.h"
#include "Table.h"

Table::~Table()
{
    close();
}

Cell *Table::parse(std::string &str)
{
    int intNum;
    double doubleNum;

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
        return new FormulaCell(str, &table);
    }
    if(str[0] == '"' && str.back() == '"') //String
    {
        std::string result = str.substr(1, str.length() - 2);
        return new StringCell(result, result.length());
    }

    return nullptr;
}

void Table::read(const std::string &path)
{
    std::ifstream file(path);
    if(!file.is_open())
    {
        std::cout << "Could not open file" << std::endl;
        return;
    }

    std::string line;
    double number = 0;
    while(getline(file, line))
    {
        std::stringstream ss(line);
        std::string param;
        std::streampos lastPos;
        size_t row = 0;
        table.push_back(std::vector<Cell *>());

        while(getline(ss, param, ','))
        {
            if(maxWidth.size() <= row) maxWidth.push_back(0);
            param = StringHelper::trim(param);

            if(param.length() > 0 && param[0] == '"')
            {
                std::string empty;
                param.clear();
                ss.clear();
                ss.seekg(lastPos);

                char ch;
                getline(ss, empty, '"');
                param += '"';
                while(ss.get(ch) && ch != '"')
                {
                    param += ch;
                    if(ch == '\\') 
                    {
                        ss.get(ch);
                        param += ch;
                    }

                }
                param += '"';
                getline(ss, empty, ',');
            }

            Cell *ptr = parse(param);
            
            if(ptr != nullptr && ptr->length > maxWidth[row]) maxWidth[row] = ptr->length;
            table[maxCols].push_back(ptr);
            

            lastPos = ss.tellg();
            row++;
        }
        if(row > maxRows) maxRows = row;
        maxCols++;
    }
}

void Table::edit()
{
    size_t row, col;
    std::string data;
    std::cin >> row >> col >> data;
    if(maxCols <= col || col < 0 || maxRows <= row || row < 0)
    {
        std::cout << "Invalid index" << std::endl;
        return;
    }

    Cell *ptr = parse(data);
    if(table[col].size() < row + 1) table[col].resize(row + 1, nullptr);

    if(table[col][row] != nullptr)
        delete table[col][row];

    if(maxWidth[row] < ptr->length) maxWidth[row] = ptr->length;
    table[col][row] = ptr;
}

void Table::help()
{
    std::cout << "print                     prints file \n"
              << "edit <row> <col> <data>	changes data  \n";
}

void Table::close()
{
    for(std::vector <Cell *> &col : table)
    {
        for(Cell * row: col)
        {
            delete row;
        }
        col.clear();
    }
    table.clear();
    maxWidth.clear();
    maxCols = 0;
    maxRows = 0;
}

std::ostream &operator <<(std::ostream &stream, Table &obj)
{

    for(int i=0; i < obj.maxCols; i++)
    {
        for(int j=0; j < obj.maxRows; j++)
        {
            if(obj.table[i].size() > j)
            {
                size_t numSpaces = obj.maxWidth[j];
                if(obj.table[i][j] != nullptr) 
                {
                    numSpaces -= obj.table[i][j]->length;
                    obj.table[i][j]->print(stream);
                }
                for(int t=0; t < numSpaces; t++) stream << " ";
            }
            else 
                for(int t=0; t < obj.maxWidth[j]; t++) stream << " ";
            stream << "| ";
        }  
        stream << std::endl;
    }
    return stream;
}