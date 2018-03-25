//
// Created by MTesseracT on 23-3-2018.
//

#ifndef VULKANENGINEFIXED_PIPELINECREATEINFO_HPP
#define VULKANENGINEFIXED_PIPELINECREATEINFO_HPP

#include <Core/Renderer/Vulkan/Assets/ShaderProgram/ShaderStages.hpp>
#include "VertexLayout.hpp"
#include "DescriptorSetLayout.hpp"

namespace mt
{
    struct PipelineCreateInfo
    {
        PipelineCreateInfo(VertexLayout p_vertexLayout,
                           DescriptorSetLayout p_descriptorSetLayout,
                           const ShaderStages& p_shaders);

        VertexLayout        m_vertexLayout;
        DescriptorSetLayout m_descriptorSetLayout;
        ShaderStages        m_shaders;
    };
}


#endif //VULKANENGINEFIXED_PIPELINECREATEINFO_HPP
