//
// Created by MTesseracT on 21-3-2018.
//

#include "ShaderStages.hpp"

namespace mt
{
    void ShaderStages::addShaderStage(vk::PipelineShaderStageCreateInfo p_shaderStage)
    {
        m_shaderStages.push_back(p_shaderStage);
    }

    void ShaderStages::setName(std::string p_name)
    {
        m_name = p_name;
    }

    const std::string& ShaderStages::getName()
    {
        return m_name;
    }

    std::vector<vk::PipelineShaderStageCreateInfo>& ShaderStages::getShaderStages()
    {
        return m_shaderStages;
    }
}

