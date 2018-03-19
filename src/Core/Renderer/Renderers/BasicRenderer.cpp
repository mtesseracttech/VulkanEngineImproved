//
// Created by MTesseracT on 15-3-2018.
//

#include <Core/Utility/Logger.hpp>
#include "BasicRenderer.hpp"

namespace mt
{
    void BasicRenderer::initialize()
    {
        Logger::log("Initializing the Renderer");

        Logger::log("Creating the Swapchain");
        m_swapchain.create();

        Logger::log("Initializing the Swapchain");
        m_swapchain.initialize();

        Logger::log("Creating the Render Pass");
        m_renderPass.create(m_swapchain);
    }

    void BasicRenderer::destroy()
    {
        Logger::log("Destroying the Render Pass");
        m_renderPass.destroy();

        Logger::log("Destroying the Swapchain");
        m_swapchain.destroy();
    }
}
