//
// Created by MTesseracT on 21-3-2018.
//

#ifndef VULKANENGINEFIXED_SHADERSTAGES_HPP
#define VULKANENGINEFIXED_SHADERSTAGES_HPP


#include <vulkan/vulkan.hpp>
#include <string>

namespace mt
{
    class ShaderStages
    {
    private:
        std::vector<vk::PipelineShaderStageCreateInfo> m_shaderStages;
        std::string                                    m_name;
    public:
        void setName(std::string p_name);

        void addShaderStage(vk::PipelineShaderStageCreateInfo p_shaderStage);

        const std::string& getName();

        std::vector<vk::PipelineShaderStageCreateInfo>& getShaderStages();
    };
}


#endif //VULKANENGINEFIXED_SHADERSTAGES_HPP
