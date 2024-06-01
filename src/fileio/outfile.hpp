#include <iostream>
#include <fstream>
#include <string>
#include "file.hpp"

#ifndef OUTFILE_HPP
#define OUTFILE_HPP

class OutFile : virtual public File
{
public:
    OutFile(std::filesystem::path path);
    void write(const std::string& data);
};

#endif
