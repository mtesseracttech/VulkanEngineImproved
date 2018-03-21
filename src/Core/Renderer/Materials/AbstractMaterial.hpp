//
// Created by MTesseracT on 21-3-2018.
//

#ifndef VULKANENGINEFIXED_ABSTRACTMATERIAL_HPP
#define VULKANENGINEFIXED_ABSTRACTMATERIAL_HPP

#include <Core/Renderer/Vulkan/Pipeline/Pipeline.hpp>

namespace mt
{
    class AbstractMaterial
    {
    protected:
        Pipeline m_pipeline;
    public:
        AbstractMaterial() = default;
        virtual ~AbstractMaterial() = default;

        virtual void create() = 0;

        virtual void initialize() = 0;
    };
}

#endif //VULKANENGINEFIXED_ABSTRACTMATERIAL_HPP
