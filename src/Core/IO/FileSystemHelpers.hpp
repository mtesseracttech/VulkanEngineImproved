//
// Created by MTesseracT on 23-3-2018.
//

#ifndef VULKANENGINEFIXED_FILESYSTEMHELPERS_HPP
#define VULKANENGINEFIXED_FILESYSTEMHELPERS_HPP

#include <string>

namespace mt
{
    namespace AssetLocations
    {
        const std::string RESOURCE_BASE = "../res/";
        const std::string SHADERS       = RESOURCE_BASE + "shaders/";
        const std::string MODELS        = RESOURCE_BASE + "models/";
        const std::string TEXTURES      = RESOURCE_BASE + "textures/";
    }

    class FileSystemHelpers
    {
    public:
        /*
         * Checks if a given file exists
         */
        static bool fileExists(const std::string& p_fileName);
        static bool folderExists(const std::string& p_folderName);
    };
}


#endif //VULKANENGINEFIXED_FILESYSTEMHELPERS_HPP
