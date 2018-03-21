//
// Created by MTesseracT on 21-3-2018.
//

#ifndef VULKANENGINEFIXED_PIPELINE_HPP
#define VULKANENGINEFIXED_PIPELINE_HPP

#include <Core/Renderer/Vulkan/Assets/ShaderProgram/ShaderStages.hpp>

namespace mt
{
    class Pipeline
    {
        void setShaderStages(ShaderStages p_stages);

        void create();

        vk::PipelineLayout m_pipelineLayout = nullptr;
        vk::Pipeline m_pipeline = nullptr;
        ShaderStages m_stages;
    };
}


#endif //VULKANENGINEFIXED_PIPELINE_HPP
