//
// Created by MTesseracT on 22-3-2018.
//

#include <Core/Renderer/Vulkan/Device/Display.hpp>
#include "PipelineCache.hpp"

namespace mt
{
    PipelineCache& PipelineCache::get()
    {
        static PipelineCache instance;
        return instance;
    }

    vk::PipelineCache& PipelineCache::getPipelineCache()
    {
        return m_cache;
    }

    PipelineCache::PipelineCache()
    {
        const auto& device = Display::get().getDevice();

        vk::PipelineCacheCreateInfo createInfo;

        m_cache = device.createPipelineCache(createInfo);
    }
}
