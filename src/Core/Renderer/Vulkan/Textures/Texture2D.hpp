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
        void load(const std::string& p_filename,
                  vk::Format p_format,
                  vk::ImageUsageFlags p_imageUsage = vk::ImageUsageFlagBits::eSampled,
                  vk::ImageLayout p_layout = vk::ImageLayout::eShaderReadOnlyOptimal,
                  bool p_linear = false);
    };
}


#endif //VULKANENGINEFIXED_TEXTURE2D_HPP
