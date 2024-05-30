#include "infile.hpp"
#include "../utilities/errors.hpp"

InFile::InFile(std::string filename) : filename{filename} {}

std::string InFile::read()
{
    std::string data;
    std::ifstream file{filename};
    if (!file)
        throw FileError("Couldn't open the file.", filename);
    file >> data;
    return data;
}
