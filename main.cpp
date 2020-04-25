#include <iostream>
#include <string>

#include "Table.h"

int main()
{
    std::string command;
    Table table;

    while(command != "exit")
    {
        std::cin >> command;
        if(command.compare("open") == 0)
        {
            std::string path;
            std::cin.ignore();
            getline(std::cin, path);
            
            table.read(path);
        }
        else if(command.compare("close") == 0)
        {
            table.close();
        }
        else if(command.compare("print") == 0)
        {
            std::cout << table << std::endl;
        }
        else if(command.compare("save") == 0)
        {
            
        }
        else if(command.compare("saveas") == 0)
        {

        }
        else if(command.compare("help") == 0)
        {
            std::cout << "The following commands are supported: \n"
                      << "open <file>	opens <file> \n"
                      << "close			closes currently opened file \n"
                      << "save			saves the currently open file \n"
                      << "saveas <file>	saves the currently open file in <file> \n"
                      << "help			prints this information \n" 
                      << "exit			exists the program \n";
            
            table.help();
        }
    }

    std::cout << "Exiting the program" << std::endl;

    return 0;
}