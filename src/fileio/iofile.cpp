#include "JSON_file.hpp"

IOFile::IOFile(std::filesystem::path path) :
    File{path}, InFile{path}, OutFile{path} {}
