//
// Created by MTesseracT on 15-3-2018.
//

#include "BasicRenderer.hpp"

namespace mt{

    void BasicRenderer::initialize()
    {
        m_swapchain.create();
        m_swapchain.initialize();
    }
}
