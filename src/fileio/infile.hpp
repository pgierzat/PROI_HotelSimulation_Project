#include <iostream>
#include <fstream>
#include <string>
#include "file.hpp"

#ifndef INFILE_HPP
#define INFILE_HPP

class InFile : virtual public File
{
public:
    InFile(std::filesystem::path path);
    std::string read();
};

#endif
