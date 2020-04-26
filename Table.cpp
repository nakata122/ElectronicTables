
#include <string>
#include <fstream>
#include <sstream>
#include "Table.h"

Table::~Table()
{
    for(std::vector <Cell *> col : table)
    {
        for(Cell * row: col)
        {
            delete row;
        }
    }
}

size_t Table::expandWidth(const std::string &str, const size_t &row)
{
    size_t first = str.find_first_not_of(' ');
    size_t last = str.find_last_not_of(' ');

    size_t width = last - first;
    if(width > maxWidth[row]) maxWidth[row] = width;

    return width;
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

            std::stringstream temp(param);
            if (temp >> number && temp.eof()) //Number
            {
                size_t width = expandWidth(param, row);
                
                table[maxCols].push_back(new TypedCell<double>(number, width));
                number = 0;
            }
            else if(param[0] == '=') //Formula
            {

            }
            else //String
            {
                std::string data, empty, result;
                ss.clear();
                ss.seekg(lastPos);
                getline(ss, empty, '"');
                while(getline(ss, data, '"'))
                {
                    result += data;
                    if(!data.empty() && data.back() == '\\') result += '"';
                    else break;
                }
                getline(ss, empty, ',');

                size_t width = expandWidth(result, row);
                
                table[maxCols].push_back(new TypedCell<std::string>(result, width));
            }

            lastPos = ss.tellg();
            row++;
        }
        if(row > maxRows) maxRows = row;
        maxCols++;
    }
}

void Table::help()
{
    std::cout << "print                     prints file \n"
              << "edit <row> <col> <data>	changes data  \n";
}

void Table::close()
{

}

std::ostream &operator <<(std::ostream &stream, Table &obj)
{

    for(int i=0; i < obj.maxCols; i++)
    {
        for(int j=0; j < obj.maxRows; j++)
        {
            if(obj.table[i].size() > j)
            {
                //std::cout << j;
                obj.table[i][j]->print(stream);
                for(int t=0; t < obj.maxWidth[j] - obj.table[i][j]->length; t++) stream << " ";
            }
            else 
                for(int t=0; t < obj.maxWidth[j] + 1; t++) stream << " ";
            stream << "| ";
        }  
        stream << std::endl;
    }
    return stream;
}