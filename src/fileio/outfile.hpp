#include <iostream>
#include <fstream>
#include <string>

#ifndef OUTFILE_HPP
#define OUTFILE_HPP

class OutFile
{
public:
    OutFile(std::string filename);
    void write(const std::string& data);
private:
    std::string filename;
};

#endif
