#ifndef FILE_HPP
#define FILE_HPP

#include <string>
#include <filesystem>

class File
{
    public:
        File(std::filesystem::path path);
    protected:
        std::filesystem::path path;
};

#endif
