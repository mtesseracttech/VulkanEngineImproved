//
// Created by MTesseracT on 22-3-2018.
//

#ifndef VULKANENGINEFIXED_MATERIALCACHE_HPP
#define VULKANENGINEFIXED_MATERIALCACHE_HPP

#include <map>
#include "AbstractMaterial.hpp"


namespace mt
{
    template<typename T>
    class MaterialCache
    {
    public:
        std::map<std::string, T> m_materials;

        void empty();

        void load(vk::RenderPass p_renderPass);
    public:
        void registerMat(std::string p_name);

        T const& getMat(std::string p_name);

        void reload(vk::RenderPass p_renderPass);
    };
}

#endif //VULKANENGINEFIXED_MATERIALCACHE_HPP
