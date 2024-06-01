#include "outfile.hpp"
#include "../utilities/errors.hpp"
#include <stdexcept>

OutFile::OutFile(std::filesystem::path path) : File{path} {}

void OutFile::write(const std::string& data)
{
    std::ofstream file{path};
    file << data;
    if (!file)
        throw FileError("Couldn't write to file.", path.c_str());
}
