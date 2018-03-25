//
// Created by MTesseracT on 20-3-2018.
//

#ifndef VULKANENGINEFIXED_PHONGMATERIAL_HPP
#define VULKANENGINEFIXED_PHONGMATERIAL_HPP

#include <Core/Renderer/Vulkan/RenderPass/RenderPass.hpp>
#include <Core/Renderer/Vulkan/Pipeline/Pipeline.hpp>
#include "AbstractMaterial.hpp"

namespace mt
{
    class PhongMaterial : public AbstractMaterial
    {
    private:
        Pipeline m_pipeline;
    public:
        PhongMaterial();
        ~PhongMaterial();

        void loadAssets(const std::string& p_assetName) override;

        void initializePipeline(RenderPass p_renderPass) override;

        void rebuild() override;
    };
}


#endif //VULKANENGINEFIXED_PHONGMATERIAL_HPP
