#include "JSON_file.hpp"
#include "../utilities/errors.hpp"

JSONFile::JSONFile(std::filesystem::path path) : File{path}, IOFile{path} {}

nlohmann::json JSONFile::read()
{
    json j;
    std::ifstream file{path};
    if (!file)
        throw FileError("Couldn't open the file.", path);
    try {
        file >> j;
    } catch(const json::exception& e) {
        throw JSONException("Error reading from JSON", j);
    }
    return j;
}

void JSONFile::write(const json& j)
{
    std::ofstream file{path};
    try {
        file << j.dump(4);
    } catch(const json::exception& e) {
        throw JSONException("Error writing to JSON", j);
    }
    if (!file)
        throw FileError("Couldn't write to JSON.", path.c_str());
}
