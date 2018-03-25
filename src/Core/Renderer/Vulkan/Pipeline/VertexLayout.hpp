//
// Created by MTesseracT on 21-3-2018.
//

#ifndef VULKANENGINEFIXED_VERTEXLAYOUT_HPP
#define VULKANENGINEFIXED_VERTEXLAYOUT_HPP

#include <vector>
#include <vulkan/vulkan.hpp>

namespace mt
{
    enum VertexLayoutComponent
    {
        ePosition,
        eNormal,
        eColor,
        eUV,
        eTangent,
        eBitangent,
        eDummyFloat,
        eDummyVec4
    };

    class VertexLayout
    {
    private:
        std::vector<VertexLayoutComponent>               m_vertexComponents;
        std::vector<vk::VertexInputBindingDescription>   m_vertexInputBindings;
        std::vector<vk::VertexInputAttributeDescription> m_vertexInputAttributes;
        uint32_t                                         m_stride;

    private:
        void calculateStride();

        void generateBindingDescription();

        void generateAttributeDescription();

    public:
        VertexLayout(std::vector<VertexLayoutComponent> p_components);

        uint32_t getStride();

        vk::VertexInputBindingDescription* const getBindings();

        vk::VertexInputAttributeDescription* const getAttributes();

        uint32_t getBindingCount();

        uint32_t getAttributeCount();
    };
}


#endif //VULKANENGINEFIXED_VERTEXLAYOUT_HPP
