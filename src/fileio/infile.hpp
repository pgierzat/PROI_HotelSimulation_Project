#include <iostream>
#include <fstream>
#include <string>

#ifndef INFILE_HPP
#define INFILE_HPP

class InFile
{
public:
    InFile(std::string filename);
    std::string read();
private:
    std::string filename;
};

#endif
