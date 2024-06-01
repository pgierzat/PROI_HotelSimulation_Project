#ifndef IO_FILE_HPP
#define IO_FILE_HPP

#include "../utilities/json.hpp"
#include "infile.hpp"
#include "outfile.hpp"

class IOFile : public InFile, public OutFile
{
    public:
        IOFile(std::filesystem::path path);
};


#endif
