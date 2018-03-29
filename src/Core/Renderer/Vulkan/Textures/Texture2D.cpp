//
// Created by MTesseracT on 29-3-2018.
//

#include <exception>
#include <Core/IO/FileSystemHelpers.hpp>
#include <sstream>
#include "Texture2D.hpp"

namespace mt
{
    void Texture2D::load(const std::string& p_filename,
                         vk::Format p_format,
                         vk::ImageUsageFlags p_imageUsage,
                         vk::ImageLayout p_layout,
                         bool p_linear)
    {
        if(FileSystemHelpers::fileExists(p_filename))
        {
            std::stringstream error;
            error << "Could not find the following texture file: " << p_filename;
            throw std::runtime_error(error.str());
        }

        
    }
}