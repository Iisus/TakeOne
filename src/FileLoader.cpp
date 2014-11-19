#include "FileLoader.h"
#include <fstream>
#include <sstream>

std::string TakeOne::FileLoader::LoadTextFile(const std::string& filePath)
{
    std::ifstream fileStream(filePath);
    std::stringstream buffer;
    buffer << fileStream.rdbuf();
    return buffer.str();
}
