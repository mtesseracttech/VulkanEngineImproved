//
// Created by MTesseracT on 15-3-2018.
//

#include <Core/Utility/Logger.hpp>
#include "BasicRenderer.hpp"
#include <sstream>
#include <Core/Renderer/Vulkan/Window/RenderWindow.hpp>
#include <Core/Renderer/Vulkan/Device/Display.hpp>
#include <Core/Renderer/Materials/PhongMaterial.hpp>

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

    void BasicRenderer::onResized()
    {
        auto& window = RenderWindow::get();
        auto& device = Display::get().getWrappedDevice();

        if(window.getSize().x == 0 || window.getSize().y == 0) return;

        device.waitTillIdle();

        Logger::log("Rebuilding Swapchain related Resources");
        m_renderPass.destroy();
        m_swapchain.destroy();
        m_swapchain.create();
        m_swapchain.initialize();
        m_renderPass.create(m_swapchain);
    }
}
