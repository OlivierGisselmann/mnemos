#include <core/filesystem/filesystem.hpp>

namespace Mnemos
{
    const std::string ReadFile(const char* filePath)
    {
        std::ifstream file;

        file.exceptions(std::ifstream::failbit | std::ifstream::badbit);

        try
        {
            std::stringstream fileContent;

            // Open file, read to sstream and close it
            file.open(filePath);
            fileContent << file.rdbuf();
            file.close();

            return fileContent.str();
        }
        catch(const std::exception& e)
        {
            return "\0";
        }
        
    }
}
