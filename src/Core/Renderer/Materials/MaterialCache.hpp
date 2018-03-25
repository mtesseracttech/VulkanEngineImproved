//
// Created by MTesseracT on 22-3-2018.
//

#ifndef VULKANENGINEFIXED_MATERIALCACHE_HPP
#define VULKANENGINEFIXED_MATERIALCACHE_HPP

#include <map>
#include <type_traits>
#include <Core/IO/FileSystemHelpers.hpp>
#include <Core/Utility/Logger.hpp>
#include "AbstractMaterial.hpp"

namespace mt
{
    template<typename T>
    class MaterialCache
    {
        static_assert(std::is_base_of<AbstractMaterial, T>::value, "Cannot add non-material to material cache (inherit from AbstractMaterial)");
    private:
        std::map<std::string, T> m_materials;

    public:
        T* load(const std::string& p_resourceName)
        {
            const auto it = m_materials.find(p_resourceName);

            //Return the resource if already cached
            if (it != m_materials.end()) return &m_materials[p_resourceName];

            //Attempt to load the resource
            if (FileSystemHelpers::folderExists(AssetLocations::TEXTURES + p_resourceName))
            {
                try
                {
                    T material;
                    material.loadAssets(p_resourceName);
                    m_materials[p_resourceName] = std::move(material);
                    return &m_materials[p_resourceName];
                }
                catch (std::runtime_error& err)
                {
                    Logger::log("Could not load material: " + p_resourceName, LogError);
                }
            }
            else {
                Logger::log("No folder for " + p_resourceName + " exists", LogError);
                Logger::log("Expected folder: " + AssetLocations::TEXTURES + p_resourceName, LogDebug);
            }


            //If no asset folder is found or an error occurred while loading a material, return nullptr
            return nullptr;
        }
    };
}

#endif //VULKANENGINEFIXED_MATERIALCACHE_HPP
