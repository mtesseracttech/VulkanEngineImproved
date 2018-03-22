//
// Created by MTesseracT on 22-3-2018.
//

#include "MaterialCache.hpp"

namespace mt
{
    template<typename T>
    T const& MaterialCache<T>::getMat(std::string p_name)
    {

    }

    template<typename T>
    void MaterialCache<T>::registerMat(std::string p_name)
    {
        m_materials[p_name] = T();
    }

    template<typename T>
    void MaterialCache<T>::reload(vk::RenderPass p_renderPass)
    {

    }

    template<typename T>

    void MaterialCache<T>::load(vk::RenderPass p_renderPass)
    {

    }

    template<typename T>
    void MaterialCache<T>::empty()
    {
        for (auto& material : m_materials)
        {
        }
    }
}
