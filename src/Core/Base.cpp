//
// Created by MTesseracT on 9-3-2018.
//

#include <Core/Renderer/Vulkan/Device/Display.hpp>
#include <Core/Utility/Logger.hpp>
#include <Core/Input/Input.hpp>
#include "Base.hpp"

namespace mt {
    void Base::Initialize()
    {
        Logger::log("Initializing Wolfsbane");
        Display::get().initialize();
        Input::get().initialize();
    }

    void Base::Run()
    {
        while(true){
        }
    }
}

