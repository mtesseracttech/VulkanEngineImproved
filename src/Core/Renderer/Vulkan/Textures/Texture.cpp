//
// Created by MTesseracT on 29-3-2018.
//

#include <Core/Renderer/Vulkan/Device/Display.hpp>
#include "Texture.hpp"

namespace mt
{
    void Texture::destroy()
    {
        const auto& device = Display::get().getDevice();

        device.destroyImageView(m_view);
        device.destroyImage(m_image);
        if (m_sampler) device.destroySampler(m_sampler);
        device.freeMemory(m_deviceMemory);
    }

    void Texture::updateDescriptor()
    {
        m_desciptorImageInfo.sampler     = m_sampler;
        m_desciptorImageInfo.imageView   = m_view;
        m_desciptorImageInfo.imageLayout = m_imageLayout;
    }
}

