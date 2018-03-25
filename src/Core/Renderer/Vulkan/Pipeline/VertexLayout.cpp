//
// Created by MTesseracT on 21-3-2018.
//

#include "VertexLayout.hpp"

namespace mt
{
    VertexLayout::VertexLayout(std::vector<VertexLayoutComponent> p_components)
    {
        m_vertexComponents = std::move(p_components);
        calculateStride();
        generateBindingDescription();
        generateAttributeDescription();
    }

    void VertexLayout::calculateStride()
    {
        uint32_t res = 0;
        for (auto& component : m_vertexComponents)
        {
            switch (component)
            {
                case eUV:
                    res += 2 * sizeof(float);
                    break;
                case eDummyFloat:
                    res += sizeof(float);
                    break;
                case eDummyVec4:
                    res += 4 * sizeof(float);
                    break;
                default:
                    res += 3 * sizeof(float);
            }
        }
        m_stride     = res;
    }

    void VertexLayout::generateBindingDescription()
    {
        vk::VertexInputBindingDescription vertexInputBindingDescription;
        vertexInputBindingDescription.binding   = 0;
        vertexInputBindingDescription.stride    = m_stride;
        vertexInputBindingDescription.inputRate = vk::VertexInputRate::eVertex;

        m_vertexInputBindings = {vertexInputBindingDescription};
    }

    void VertexLayout::generateAttributeDescription()
    {
        m_vertexInputAttributes.resize(m_vertexComponents.size());

        uint32_t offset = 0;

        for (uint32_t i = 0; i < m_vertexComponents.size(); ++i)
        {
            const auto& comp = m_vertexComponents[i];

            vk::VertexInputAttributeDescription description;
            description.binding  = 0;
            description.location = i;
            description.offset   = offset;

            switch (comp)
            {
                case eDummyFloat:
                    description.format = vk::Format::eR32Sfloat;
                    offset += 1 * sizeof(float);
                    break;
                case eUV:
                    description.format = vk::Format::eR32G32Sfloat;
                    offset += 2 * sizeof(float);
                    break;
                case eDummyVec4:
                    description.format = vk::Format::eR32G32B32A32Sfloat;
                    offset += 4 * sizeof(float);
                    break;
                default:
                    description.format = vk::Format::eR32G32B32Sfloat;
                    offset += 3 * sizeof(float);
            }

            m_vertexInputAttributes[i] = description;
        }
    }

    uint32_t VertexLayout::getStride()
    {
        return m_stride;
    }

    vk::VertexInputBindingDescription* const VertexLayout::getBindings()
    {
        return m_vertexInputBindings.data();
    }

    vk::VertexInputAttributeDescription* const VertexLayout::getAttributes()
    {
        return m_vertexInputAttributes.data();
    }

    uint32_t VertexLayout::getBindingCount()
    {
        return static_cast<uint32_t>(m_vertexInputBindings.size());
    }

    uint32_t VertexLayout::getAttributeCount()
    {
        return static_cast<uint32_t >(m_vertexInputAttributes.size());
    }
}