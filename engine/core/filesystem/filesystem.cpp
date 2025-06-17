#include <core/filesystem/filesystem.hpp>

namespace Mnemos
{
    // Store the exe's dir
    static std::filesystem::path sExecutablePath = std::filesystem::current_path();

    std::filesystem::path ResolvePath(const std::filesystem::path& inputPath)
    {
        if(inputPath.is_absolute())
            return inputPath;
        else
            return std::filesystem::absolute(sExecutablePath / inputPath);
    }

    const std::string ReadFile(const char* filePath)
    {
        std::ifstream file;

        file.exceptions(std::ifstream::failbit | std::ifstream::badbit);

        try
        {
            std::stringstream fileContent;

            // Open file, read to sstream and close it
            file.open(ResolvePath(filePath));
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
