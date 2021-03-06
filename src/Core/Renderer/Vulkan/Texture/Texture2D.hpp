//
// Created by MTesseracT on 29-3-2018.
//

#ifndef VULKANENGINEFIXED_TEXTURE2D_HPP
#define VULKANENGINEFIXED_TEXTURE2D_HPP

#include "Texture.hpp"

namespace mt
{
    class Texture2D : Texture
    {
    public:
        void load(const std::string& p_filename, vk::ImageUsageFlags p_imageUsage, vk::ImageLayout p_layout) override;
    };
}


#endif //VULKANENGINEFIXED_TEXTURE2D_HPP
