#ifndef JSON_FILE_HPP
#define JSON_FILE_HPP

#include "iofile.hpp"
#include "../utilities/json.hpp"


class JSONFile : public IOFile
{
    using json = nlohmann::json;
    public:
        JSONFile(std::filesystem::path path);
        json read();
        void write(const json&);
};


#endif
