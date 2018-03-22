//
// Created by MTesseracT on 22-3-2018.
//

#ifndef VULKANENGINEFIXED_PIPELINECACHE_HPP
#define VULKANENGINEFIXED_PIPELINECACHE_HPP


#include <vulkan/vulkan.hpp>

namespace mt{
    class PipelineCache
    {
        vk::PipelineCache m_cache;
        PipelineCache();
    public:
        static PipelineCache& get();

        vk::PipelineCache& getPipelineCache();
    };
}



#endif //VULKANENGINEFIXED_PIPELINECACHE_HPP
