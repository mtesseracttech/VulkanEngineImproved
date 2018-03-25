//
// Created by MTesseracT on 19-3-2018.
//

#ifndef VULKANENGINEFIXED_SHADERPROGRAM_HPP
#define VULKANENGINEFIXED_SHADERPROGRAM_HPP

#include <vulkan/vulkan.hpp>
#include <string>
#include "ShaderStages.hpp"

namespace mt
{
    class ShaderProgram
    {
        /*
         * Note: making a distinction between filename and shadername on purpose, loadshader will load an entire folder of appropriately named files in one go.
         * Functions that have filename will work on the specific files
         */

        /*
         * Reads the file as a binary and returns a list of the characters
         */
        static std::vector<char> readFile(std::string& p_fileName);

        /*
         * Creates a module out of the shader code
         */
        static vk::ShaderModule createShaderModule(const std::vector<char>& code);

    public:
        /*
         * Call this to load a shader folder, it's expected to be in the following format/location:
         * (proj_root)/res/shaders/(shader_name)/(shader_name).type.spv
         *
         * The types/fileexts that are looked for are:
         *
         * Fragment - .frag.spv
         * Vertex   - .vert.spv
         * Geometry - .geom.spv
         */
        static ShaderStages loadShader(const std::string& p_shaderName);
    };
}


#endif //VULKANENGINEFIXED_SHADERPROGRAM_HPP
