
#include <string>
#include <fstream>
#include <sstream>
#include "Table.h"

void Table::read(const std::string &path)
{
    std::ifstream file(path);
    if(!file.is_open())
    {
        std::cout << "Could not open file" << std::endl;
        return;
    }

    std::string line;
    double number;
    while(getline(file, line))
    {
        std::stringstream ss(line);
        std::string param;
        std::streampos lastPos;

        while(getline(ss, param, ','))
        {
            std::stringstream temp(param);
            if (temp >> number && temp.eof()) //Number
            {
                std::cout << number << " ";
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

                std::cout << result << " ";
            }

            lastPos = ss.tellg();
        }
        std::cout << std::endl;
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
    return stream;
}