//
// Created by MTesseracT on 15-3-2018.
//

#include <Core/Utility/Logger.hpp>
#include "BasicRenderer.hpp"

namespace mt{

    void BasicRenderer::initialize()
    {
        Logger::log("Initializing the Renderer");
        m_swapchain.create();
        m_swapchain.initialize();
        m_renderPass.create(m_swapchain);
    }
}
