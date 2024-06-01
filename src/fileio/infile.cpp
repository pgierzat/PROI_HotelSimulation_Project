#include "infile.hpp"
#include "../utilities/errors.hpp"

InFile::InFile(std::filesystem::path path) : File{path} {}

std::string InFile::read()
{
    std::string data;
    std::ifstream file{path};
    if (!file)
        throw FileError("Couldn't open the file.", path);
    file >> data;
    return data;
}
