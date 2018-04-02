//
// Created by MTesseracT on 20-3-2018.
//

#ifndef VULKANENGINEFIXED_PHONGMATERIAL_HPP
#define VULKANENGINEFIXED_PHONGMATERIAL_HPP

#include <Core/Renderer/Vulkan/RenderPass/RenderPass.hpp>
#include <Core/Renderer/Vulkan/Pipeline/Pipeline.hpp>
#include <Core/Renderer/Vulkan/Texture/Texture2D.hpp>
#include <Core/Renderer/Vulkan/Buffer/UniformBuffer.hpp>
#include "AbstractMaterial.hpp"
#include "MaterialCache.hpp"

namespace mt
{
    class PhongMaterial : public AbstractMaterial
    {
    private:
        template<typename T>
        friend class MaterialCache;

    protected:
        Pipeline m_pipeline;

        Texture2D m_texture;

        UniformBuffer m_uniformBuffer;

        struct UniformBufferObject {
            glm::mat4 model;
            glm::mat4 view;
            glm::mat4 proj;
        } m_ubo;

    public:
        PhongMaterial();

        ~PhongMaterial() override;

        void update(const glm::mat4& p_model, const glm::mat4& p_view, const glm::mat4& p_proj);

    protected:
        void loadAssets(const std::string& p_assetName) override;

        void initializePipeline(const RenderPass& p_renderPass) override;
    public:
        static PhongMaterial const * const load(const std::string& p_assetName);
    };

    namespace PhongMaterialLoader
    {
        static MaterialCache<PhongMaterial> m_cache;
    };

}


#endif //VULKANENGINEFIXED_PHONGMATERIAL_HPP
