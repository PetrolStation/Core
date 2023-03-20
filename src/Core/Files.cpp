#include <PCH.h>

#include "Files.h"

#include <fstream>

// TODO: review this script

namespace PetrolEngine {
    String ReadFile(const String& filepath) {
        std::string result;
        std::ifstream in(filepath, std::ios::in | std::ios::binary); // ifstream closes itself due to RAII

        if (!in) { LOG("Failed to read content of file(" + filepath + ")", 3); return ""; }

        in.seekg(0, std::ios::end);
        long size = in.tellg();

        if (size == -1) { LOG("Failed to read content of file(" + filepath + ")", 3); return ""; }

        result.resize(size);

        in.seekg(0, std::ios::beg);
        in.read(&result[0], size);

        return result;
    }

    String WriteFile(const String& filepath, const String& content){
        /*std::ifstream in(filepath, std::ios::out | std::ios::in | std::ios::binary); // ifstream closes itself due to RAII

        if (!in) { LOG("Failed to read content of file(" + filepath + ")", 3); return ""; }

        if (size == -1) { LOG("Failed to read content of file(" + filepath + ")", 3); return ""; }

        in.seekg(0, std::ios::beg);
        in.w
        in.read(&result[0], size);
*/
        return ""; // result;
    }
}
