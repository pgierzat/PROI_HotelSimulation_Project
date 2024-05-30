#include "outfile.hpp"
#include <stdexcept>

OutFile::OutFile(std::string filename) : filename{filename} {}

void OutFile::write(const std::string& data)
{
    std::ofstream file{filename};
    if (!file)
        throw std::invalid_argument("Couldn't open the file");
    file << data;
}
