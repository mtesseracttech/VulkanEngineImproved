//
// Created by MTesseracT on 19-3-2018.
//

#include "ShaderProgram.hpp"
#include <iostream>
#include <fstream>
#include <sstream>
#include <tuple>
#include <Core/Renderer/Vulkan/Device/Display.hpp>

namespace mt
{
    bool ShaderProgram::fileExists(std::string p_fileName)
    {
        std::ifstream file(p_fileName.c_str());
        return file.good();
    }

    std::vector<char> ShaderProgram::readFile(std::string& p_fileName)
    {
        std::ifstream file(p_fileName, std::ios::ate | std::ios::binary);

        if (!file.is_open())
        {
            throw std::runtime_error("Failed to open file!: " + p_fileName);
        }

        auto fileSize = static_cast<size_t>(file.tellg());

        std::vector<char> buffer(fileSize);

        file.seekg(0);
        file.read(buffer.data(), fileSize);

        file.close();

        return buffer;
    }

    ShaderProgram::ShaderInfo ShaderProgram::loadShader(const std::string& p_shaderName)
    {
        ShaderInfo shaderInfo;

        shaderInfo.m_name = p_shaderName;

        std::stringstream fileBase;

        fileBase << "../res/shaders/" << p_shaderName << "/" << p_shaderName;
        fileBase.flush();

        const std::array<std::tuple<std::string, vk::ShaderStageFlagBits>, 3> shaderTypes{
                std::make_tuple(".vert.spv", vk::ShaderStageFlagBits::eVertex),
                std::make_tuple(".geom.spv", vk::ShaderStageFlagBits::eGeometry),
                std::make_tuple(".frag.spv", vk::ShaderStageFlagBits::eFragment)
        };

        for (const auto& shaderType : shaderTypes)
        {
            std::string file = fileBase.str() + std::get<0>(shaderType);
            if(fileExists(file))
            {
                vk::PipelineShaderStageCreateInfo createInfo;
                createInfo.module = createShaderModule(readFile(file));
                createInfo.stage = std::get<1>(shaderType);
                createInfo.pName = "main";

                shaderInfo.m_shaderStages.push_back(createInfo);
            }
        }

        return shaderInfo;
    }

    vk::ShaderModule ShaderProgram::createShaderModule(const std::vector<char>& code)
    {
        assert(!code.empty());

        const auto& device = Display::get().getDevice();

        vk::ShaderModuleCreateInfo createInfo;
        createInfo.codeSize = code.size();
        createInfo.pCode    = reinterpret_cast<const uint32_t*>(code.data());

        return device.createShaderModule(createInfo);
    }


}