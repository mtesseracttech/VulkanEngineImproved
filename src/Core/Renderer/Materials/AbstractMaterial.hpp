//
// Created by MTesseracT on 21-3-2018.
//

#ifndef VULKANENGINEFIXED_ABSTRACTMATERIAL_HPP
#define VULKANENGINEFIXED_ABSTRACTMATERIAL_HPP

#include <Core/Renderer/Vulkan/RenderPass/RenderPass.hpp>

namespace mt
{
    class AbstractMaterial
    {
    public:
        /*
         * Set up member variables like vertex layout and descriptor layout also set up the pipeline
         */
        AbstractMaterial() = default;

        virtual ~AbstractMaterial() = default;

    protected:
        /*
         * Binding assets (textures, etc.) to the pipeline
         */
        virtual void loadAssets(const std::string& p_assetName) = 0;

        /*
         * Creating the pipeline to be used
         */
        virtual void initializePipeline(const RenderPass& p_renderPass) = 0;
    };
}

#endif //VULKANENGINEFIXED_ABSTRACTMATERIAL_HPP
