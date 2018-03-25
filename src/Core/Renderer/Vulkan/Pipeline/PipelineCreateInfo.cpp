//
// Created by MTesseracT on 23-3-2018.
//

#include "PipelineCreateInfo.hpp"

namespace mt
{

    PipelineCreateInfo::PipelineCreateInfo(VertexLayout p_vertexLayout, DescriptorSetLayout p_descriptorSetLayout,
                                           const ShaderStages& p_shaders) : m_vertexLayout(std::move(p_vertexLayout)), m_descriptorSetLayout(std::move(p_descriptorSetLayout)), m_shaders(p_shaders)
    {}
}