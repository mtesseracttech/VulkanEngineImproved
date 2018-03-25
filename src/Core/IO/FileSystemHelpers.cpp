//
// Created by MTesseracT on 23-3-2018.
//

#include "FileSystemHelpers.hpp"
#include <fstream>
#include <sys/stat.h>


namespace mt
{
    bool FileSystemHelpers::fileExists(const std::string& p_fileName)
    {
        std::ifstream file(p_fileName);
        return file.good();
    }

    bool FileSystemHelpers::folderExists(const std::string& p_folderName)
    {
        struct stat info{};
        return !stat(p_folderName.c_str(), &info);
    }
}

