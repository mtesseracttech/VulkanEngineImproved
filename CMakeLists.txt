cmake_minimum_required(VERSION 3.9)
project(VulkanEngineFixed)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(SOURCE_FILES src/EntryPoint.cpp src/Core/Renderer/Vulkan/Device/Display.cpp src/Core/Renderer/Vulkan/Device/Display.hpp src/Core/Renderer/Vulkan/Window/RenderWindow.cpp src/Core/Renderer/Vulkan/Window/RenderWindow.hpp src/Core/Base.cpp src/Core/Base.hpp src/Core/Utility/Logger.cpp src/Core/Utility/Logger.hpp src/Core/Renderer/Vulkan/Queue/DeviceQueueFamilies.cpp src/Core/Renderer/Vulkan/Queue/DeviceQueueFamilies.hpp src/Core/Renderer/Vulkan/Queue/SurfaceQueueFamilies.cpp src/Core/Renderer/Vulkan/Queue/SurfaceQueueFamilies.hpp src/Core/Renderer/Vulkan/Debug/VulkanDebug.cpp src/Core/Renderer/Vulkan/Debug/VulkanDebug.hpp src/Core/Input/KeyInput.cpp src/Core/Input/KeyInput.hpp src/Core/Input/MouseInput.cpp src/Core/Input/MouseInput.hpp src/Core/Maths/Time/Timer.cpp src/Core/Maths/Time/Timer.hpp src/Core/Maths/Time/GameTimer.cpp src/Core/Maths/Time/GameTimer.hpp src/Core/Renderer/Vulkan/Device/Device.cpp src/Core/Renderer/Vulkan/Device/Device.hpp src/Core/Renderer/Renderers/BasicRenderer.cpp src/Core/Renderer/Renderers/BasicRenderer.hpp src/Core/Renderer/Vulkan/Swapchain/Swapchain.cpp src/Core/Renderer/Vulkan/Swapchain/Swapchain.hpp src/Core/Renderer/Vulkan/Swapchain/FrameBuffer.cpp src/Core/Renderer/Vulkan/Swapchain/FrameBuffer.hpp src/Core/Renderer/Vulkan/RenderPass/RenderPass.cpp src/Core/Renderer/Vulkan/RenderPass/RenderPass.hpp src/Core/Renderer/Vulkan/RenderPass/DepthStencil.cpp src/Core/Renderer/Vulkan/RenderPass/DepthStencil.hpp src/Core/Renderer/Vulkan/Helpers/VulkanHelpers.cpp src/Core/Renderer/Vulkan/Helpers/VulkanHelpers.hpp src/Core/Renderer/Vulkan/Assets/ShaderProgram/ShaderProgram.cpp src/Core/Renderer/Vulkan/Assets/ShaderProgram/ShaderProgram.hpp)

add_executable(VulkanEngineFixed ${SOURCE_FILES})

#Sets a base path for the includes so that they can be used in the same way as in Visual Studio/Codeblocks
set(BASEPATH "${CMAKE_SOURCE_DIR}/src")
include_directories("${BASEPATH}")

#Setting up PkgConfig

find_package(PkgConfig REQUIRED)

#Finding and linking GLFW3

pkg_search_module(GLFW3 3.2 REQUIRED glfw3)
if(GLFW3_FOUND)
    message(STATUS "Found GLFW, Including and Linking now")
    include_directories(${GLFW3_INCLUDE_DIRS})
    target_link_libraries(VulkanEngineFixed ${GLFW3_STATIC_LIBRARIES})
endif(GLFW3_FOUND)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/modules/")

#Finding and linking Vulkan

find_package (Vulkan)
if (Vulkan_FOUND)
    message(STATUS "Found Vulkan, Including and Linking now")
    include_directories(${Vulkan_INCLUDE_DIRS})
    target_link_libraries (VulkanEngineFixed ${Vulkan_LIBRARIES})
    message(STATUS "Vulkan Include dirs: ${Vulkan_INCLUDE_DIRS} and libs: ${Vulkan_LIBRARIES}")
endif (Vulkan_FOUND)
#Finding and linking ASSIMP

find_package(ASSIMP REQUIRED)
if(ASSIMP_FOUND)
    message(STATUS "Found ASSIMP, Including and Linking now")
    include_directories(${ASSIMP_INCLUDE_DIR})
    target_link_libraries (VulkanEngineFixed ${ASSIMP_LIBRARY})
    #message(STATUS ${ASSIMP_INCLUDE_DIR})
endif (ASSIMP_FOUND)