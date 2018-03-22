//
// Created by MTesseracT on 20-3-2018.
//

#ifndef VULKANENGINEFIXED_PHONGMATERIAL_HPP
#define VULKANENGINEFIXED_PHONGMATERIAL_HPP

#include "AbstractMaterial.hpp"

namespace mt
{
    class PhongMaterial : public AbstractMaterial
    {
    public:
        PhongMaterial();

        void create() override;

        void initialize(vk::RenderPass p_renderPass) override;
    };
}


#endif //VULKANENGINEFIXED_PHONGMATERIAL_HPP
