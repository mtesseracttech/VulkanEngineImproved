//
// Created by MTesseracT on 29-3-2018.
//

#include <Core/Renderer/Vulkan/Device/Display.hpp>
#include <map>
#include <sstream>
#include "Texture.hpp"

namespace mt
{
    void Texture::destroy()
    {
        const auto& device = Display::get().getDevice();

        device.destroyImageView(m_view);
        device.destroyImage(m_image);
        if (m_sampler) device.destroySampler(m_sampler);
        device.freeMemory(m_deviceMemory);
    }

    void Texture::updateDescriptor()
    {
        m_descriptorImageInfo.sampler     = m_sampler;
        m_descriptorImageInfo.imageView   = m_view;
        m_descriptorImageInfo.imageLayout = m_imageLayout;
    }

    vk::Format Texture::getVulkanFormat(gli::format p_format)
    {
        switch (p_format)
        {
            case gli::FORMAT_UNDEFINED: return vk::Format::eUndefined;
            case gli::FORMAT_RG4_UNORM_PACK8: return vk::Format::eR4G4UnormPack8;
            case gli::FORMAT_RGBA4_UNORM_PACK16: return vk::Format::eR4G4B4A4UnormPack16;
            case gli::FORMAT_BGRA4_UNORM_PACK16: return vk::Format::eB4G4R4A4UnormPack16;
            case gli::FORMAT_R5G6B5_UNORM_PACK16: return vk::Format::eR5G6B5UnormPack16;
            case gli::FORMAT_B5G6R5_UNORM_PACK16: return vk::Format::eB5G6R5UnormPack16;
            case gli::FORMAT_RGB5A1_UNORM_PACK16: return vk::Format::eR5G5B5A1UnormPack16;
            case gli::FORMAT_BGR5A1_UNORM_PACK16: return vk::Format::eB5G5R5A1UnormPack16;
            case gli::FORMAT_A1RGB5_UNORM_PACK16: return vk::Format::eA1R5G5B5UnormPack16;
            case gli::FORMAT_R8_UNORM_PACK8: return vk::Format::eR8Unorm;
            case gli::FORMAT_R8_SNORM_PACK8: return vk::Format::eR8Snorm;
            case gli::FORMAT_R8_USCALED_PACK8: return vk::Format::eR8Uscaled;
            case gli::FORMAT_R8_SSCALED_PACK8: return vk::Format::eR8Sscaled;
            case gli::FORMAT_R8_UINT_PACK8: return vk::Format::eR8Uint;
            case gli::FORMAT_R8_SINT_PACK8: return vk::Format::eR8Sint;
            case gli::FORMAT_R8_SRGB_PACK8: return vk::Format::eR8Srgb;
            case gli::FORMAT_RG8_UNORM_PACK8: return vk::Format::eR8G8Unorm;
            case gli::FORMAT_RG8_SNORM_PACK8: return vk::Format::eR8G8Snorm;
            case gli::FORMAT_RG8_USCALED_PACK8: return vk::Format::eR8G8Uscaled;
            case gli::FORMAT_RG8_SSCALED_PACK8: return vk::Format::eR8G8Sscaled;
            case gli::FORMAT_RG8_UINT_PACK8: return vk::Format::eR8G8Uint;
            case gli::FORMAT_RG8_SINT_PACK8: return vk::Format::eR8G8Sint;
            case gli::FORMAT_RG8_SRGB_PACK8: return vk::Format::eR8G8Srgb;
            case gli::FORMAT_RGB8_UNORM_PACK8: return vk::Format::eR8G8B8Unorm;
            case gli::FORMAT_RGB8_SNORM_PACK8: return vk::Format::eR8G8B8Snorm;
            case gli::FORMAT_RGB8_USCALED_PACK8: return vk::Format::eR8G8B8Uscaled;
            case gli::FORMAT_RGB8_SSCALED_PACK8: return vk::Format::eR8G8B8Sscaled;
            case gli::FORMAT_RGB8_UINT_PACK8: return vk::Format::eR8G8B8Uint;
            case gli::FORMAT_RGB8_SINT_PACK8: return vk::Format::eR8G8B8Sint;
            case gli::FORMAT_RGB8_SRGB_PACK8: return vk::Format::eR8G8B8Srgb;
            case gli::FORMAT_BGR8_UNORM_PACK8: return vk::Format::eB8G8R8Unorm;
            case gli::FORMAT_BGR8_SNORM_PACK8: return vk::Format::eB8G8R8Snorm;
            case gli::FORMAT_BGR8_USCALED_PACK8: return vk::Format::eB8G8R8Uscaled;
            case gli::FORMAT_BGR8_SSCALED_PACK8: return vk::Format::eB8G8R8Sscaled;
            case gli::FORMAT_BGR8_UINT_PACK8: return vk::Format::eB8G8R8Uint;
            case gli::FORMAT_BGR8_SINT_PACK8: return vk::Format::eB8G8R8Sint;
            case gli::FORMAT_BGR8_SRGB_PACK8: return vk::Format::eB8G8R8Srgb;
            case gli::FORMAT_RGBA8_UNORM_PACK8: return vk::Format::eR8G8B8A8Unorm;
            case gli::FORMAT_RGBA8_SNORM_PACK8: return vk::Format::eR8G8B8A8Snorm;
            case gli::FORMAT_RGBA8_USCALED_PACK8: return vk::Format::eR8G8B8A8Uscaled;
            case gli::FORMAT_RGBA8_SSCALED_PACK8: return vk::Format::eR8G8B8A8Sscaled;
            case gli::FORMAT_RGBA8_UINT_PACK8: return vk::Format::eR8G8B8A8Uint;
            case gli::FORMAT_RGBA8_SINT_PACK8: return vk::Format::eR8G8B8A8Sint;
            case gli::FORMAT_RGBA8_SRGB_PACK8: return vk::Format::eR8G8B8A8Srgb;
            case gli::FORMAT_BGRA8_UNORM_PACK8: return vk::Format::eB8G8R8A8Unorm;
            case gli::FORMAT_BGRA8_SNORM_PACK8: return vk::Format::eB8G8R8A8Snorm;
            case gli::FORMAT_BGRA8_USCALED_PACK8: return vk::Format::eB8G8R8A8Uscaled;
            case gli::FORMAT_BGRA8_SSCALED_PACK8: return vk::Format::eB8G8R8A8Sscaled;
            case gli::FORMAT_BGRA8_UINT_PACK8: return vk::Format::eB8G8R8A8Uint;
            case gli::FORMAT_BGRA8_SINT_PACK8: return vk::Format::eB8G8R8A8Sint;
            case gli::FORMAT_BGRA8_SRGB_PACK8: return vk::Format::eB8G8R8A8Srgb;
            case gli::FORMAT_RGBA8_UNORM_PACK32: return vk::Format::eA8B8G8R8UnormPack32;
            case gli::FORMAT_RGBA8_SNORM_PACK32: return vk::Format::eA8B8G8R8SnormPack32;
            case gli::FORMAT_RGBA8_USCALED_PACK32: return vk::Format::eA8B8G8R8UscaledPack32;
            case gli::FORMAT_RGBA8_SSCALED_PACK32: return vk::Format::eA8B8G8R8SscaledPack32;
            case gli::FORMAT_RGBA8_UINT_PACK32: return vk::Format::eA8B8G8R8UintPack32;
            case gli::FORMAT_RGBA8_SINT_PACK32: return vk::Format::eA8B8G8R8SintPack32;
            case gli::FORMAT_RGBA8_SRGB_PACK32: return vk::Format::eA8B8G8R8SrgbPack32;
            case gli::FORMAT_RGB10A2_UNORM_PACK32: return vk::Format::eA2R10G10B10UnormPack32;
            case gli::FORMAT_RGB10A2_SNORM_PACK32: return vk::Format::eA2R10G10B10SnormPack32;
            case gli::FORMAT_RGB10A2_USCALED_PACK32: return vk::Format::eA2R10G10B10UscaledPack32;
            case gli::FORMAT_RGB10A2_SSCALED_PACK32: return vk::Format::eA2R10G10B10SscaledPack32;
            case gli::FORMAT_RGB10A2_UINT_PACK32: return vk::Format::eA2R10G10B10UintPack32;
            case gli::FORMAT_RGB10A2_SINT_PACK32: return vk::Format::eA2R10G10B10SintPack32;
            case gli::FORMAT_BGR10A2_UNORM_PACK32: return vk::Format::eA2B10G10R10UnormPack32;
            case gli::FORMAT_BGR10A2_SNORM_PACK32: return vk::Format::eA2B10G10R10SnormPack32;
            case gli::FORMAT_BGR10A2_USCALED_PACK32: return vk::Format::eA2B10G10R10UscaledPack32;
            case gli::FORMAT_BGR10A2_SSCALED_PACK32: return vk::Format::eA2B10G10R10SscaledPack32;
            case gli::FORMAT_BGR10A2_UINT_PACK32: return vk::Format::eA2B10G10R10UintPack32;
            case gli::FORMAT_BGR10A2_SINT_PACK32: return vk::Format::eA2B10G10R10SintPack32;
            case gli::FORMAT_R16_UNORM_PACK16: return vk::Format::eR16Unorm;
            case gli::FORMAT_R16_SNORM_PACK16: return vk::Format::eR16Snorm;
            case gli::FORMAT_R16_USCALED_PACK16: return vk::Format::eR16Uscaled;
            case gli::FORMAT_R16_SSCALED_PACK16: return vk::Format::eR16Sscaled;
            case gli::FORMAT_R16_UINT_PACK16: return vk::Format::eR16Uint;
            case gli::FORMAT_R16_SINT_PACK16: return vk::Format::eR16Sint;
            case gli::FORMAT_R16_SFLOAT_PACK16: return vk::Format::eR16Sfloat;
            case gli::FORMAT_RG16_UNORM_PACK16: return vk::Format::eR16G16Unorm;
            case gli::FORMAT_RG16_SNORM_PACK16: return vk::Format::eR16G16Snorm;
            case gli::FORMAT_RG16_USCALED_PACK16: return vk::Format::eR16G16Uscaled;
            case gli::FORMAT_RG16_SSCALED_PACK16: return vk::Format::eR16G16Sscaled;
            case gli::FORMAT_RG16_UINT_PACK16: return vk::Format::eR16G16Uint;
            case gli::FORMAT_RG16_SINT_PACK16: return vk::Format::eR16G16Sint;
            case gli::FORMAT_RG16_SFLOAT_PACK16: return vk::Format::eR16G16Sfloat;
            case gli::FORMAT_RGB16_UNORM_PACK16: return vk::Format::eR16G16B16Unorm;
            case gli::FORMAT_RGB16_SNORM_PACK16: return vk::Format::eR16G16B16Snorm;
            case gli::FORMAT_RGB16_USCALED_PACK16: return vk::Format::eR16G16B16Uscaled;
            case gli::FORMAT_RGB16_SSCALED_PACK16: return vk::Format::eR16G16B16Sscaled;
            case gli::FORMAT_RGB16_UINT_PACK16: return vk::Format::eR16G16B16Uint;
            case gli::FORMAT_RGB16_SINT_PACK16: return vk::Format::eR16G16B16Sint;
            case gli::FORMAT_RGB16_SFLOAT_PACK16: return vk::Format::eR16G16B16Sfloat;
            case gli::FORMAT_RGBA16_UNORM_PACK16: return vk::Format::eR16G16B16A16Unorm;
            case gli::FORMAT_RGBA16_SNORM_PACK16: return vk::Format::eR16G16B16A16Snorm;
            case gli::FORMAT_RGBA16_USCALED_PACK16: return vk::Format::eR16G16B16A16Uscaled;
            case gli::FORMAT_RGBA16_SSCALED_PACK16: return vk::Format::eR16G16B16A16Sscaled;
            case gli::FORMAT_RGBA16_UINT_PACK16: return vk::Format::eR16G16B16A16Uint;
            case gli::FORMAT_RGBA16_SINT_PACK16: return vk::Format::eR16G16B16A16Sint;
            case gli::FORMAT_RGBA16_SFLOAT_PACK16: return vk::Format::eR16G16B16A16Sfloat;
            case gli::FORMAT_R32_UINT_PACK32: return vk::Format::eR32Uint;
            case gli::FORMAT_R32_SINT_PACK32: return vk::Format::eR32Sint;
            case gli::FORMAT_R32_SFLOAT_PACK32: return vk::Format::eR32Sfloat;
            case gli::FORMAT_RG32_UINT_PACK32: return vk::Format::eR32G32Uint;
            case gli::FORMAT_RG32_SINT_PACK32: return vk::Format::eR32G32Sint;
            case gli::FORMAT_RG32_SFLOAT_PACK32: return vk::Format::eR32G32Sfloat;
            case gli::FORMAT_RGB32_UINT_PACK32: return vk::Format::eR32G32B32Uint;
            case gli::FORMAT_RGB32_SINT_PACK32: return vk::Format::eR32G32B32Sint;
            case gli::FORMAT_RGB32_SFLOAT_PACK32: return vk::Format::eR32G32B32Sfloat;
            case gli::FORMAT_RGBA32_UINT_PACK32: return vk::Format::eR32G32B32A32Uint;
            case gli::FORMAT_RGBA32_SINT_PACK32: return vk::Format::eR32G32B32A32Sint;
            case gli::FORMAT_RGBA32_SFLOAT_PACK32: return vk::Format::eR32G32B32A32Sfloat;
            case gli::FORMAT_R64_UINT_PACK64: return vk::Format::eR64Uint;
            case gli::FORMAT_R64_SINT_PACK64: return vk::Format::eR64Sint;
            case gli::FORMAT_R64_SFLOAT_PACK64: return vk::Format::eR64Sfloat;
            case gli::FORMAT_RG64_UINT_PACK64: return vk::Format::eR64G64Uint;
            case gli::FORMAT_RG64_SINT_PACK64: return vk::Format::eR64G64Sint;
            case gli::FORMAT_RG64_SFLOAT_PACK64: return vk::Format::eR64G64Sfloat;
            case gli::FORMAT_RGB64_UINT_PACK64: return vk::Format::eR64G64B64Uint;
            case gli::FORMAT_RGB64_SINT_PACK64: return vk::Format::eR64G64B64Sint;
            case gli::FORMAT_RGB64_SFLOAT_PACK64: return vk::Format::eR64G64B64Sfloat;
            case gli::FORMAT_RGBA64_UINT_PACK64: return vk::Format::eR64G64B64A64Uint;
            case gli::FORMAT_RGBA64_SINT_PACK64: return vk::Format::eR64G64B64A64Sint;
            case gli::FORMAT_RGBA64_SFLOAT_PACK64: return vk::Format::eR64G64B64A64Sfloat;
            case gli::FORMAT_RG11B10_UFLOAT_PACK32: return vk::Format::eB10G11R11UfloatPack32;
            case gli::FORMAT_RGB9E5_UFLOAT_PACK32: return vk::Format::eE5B9G9R9UfloatPack32;
            case gli::FORMAT_D16_UNORM_PACK16: return vk::Format::eD16Unorm;
            case gli::FORMAT_D24_UNORM_PACK32: return vk::Format::eX8D24UnormPack32;
            case gli::FORMAT_D32_SFLOAT_PACK32: return vk::Format::eD32Sfloat;
            case gli::FORMAT_S8_UINT_PACK8: return vk::Format::eS8Uint;
            case gli::FORMAT_D16_UNORM_S8_UINT_PACK32: return vk::Format::eD16UnormS8Uint;
            case gli::FORMAT_D24_UNORM_S8_UINT_PACK32: return vk::Format::eD24UnormS8Uint;
            case gli::FORMAT_D32_SFLOAT_S8_UINT_PACK64: return vk::Format::eD32SfloatS8Uint;
            case gli::FORMAT_RGB_DXT1_UNORM_BLOCK8: return vk::Format::eBc1RgbUnormBlock;
            case gli::FORMAT_RGB_DXT1_SRGB_BLOCK8: return vk::Format::eBc1RgbSrgbBlock;
            case gli::FORMAT_RGBA_DXT1_UNORM_BLOCK8: return vk::Format::eBc1RgbaUnormBlock;
            case gli::FORMAT_RGBA_DXT1_SRGB_BLOCK8: return vk::Format::eBc1RgbaSrgbBlock;
            case gli::FORMAT_RGBA_DXT3_UNORM_BLOCK16: return vk::Format::eBc2UnormBlock;
            case gli::FORMAT_RGBA_DXT3_SRGB_BLOCK16: return vk::Format::eBc2SrgbBlock;
            case gli::FORMAT_RGBA_DXT5_UNORM_BLOCK16: return vk::Format::eBc3UnormBlock;
            case gli::FORMAT_RGBA_DXT5_SRGB_BLOCK16: return vk::Format::eBc3SrgbBlock;
            case gli::FORMAT_R_ATI1N_UNORM_BLOCK8: return vk::Format::eBc4UnormBlock;
            case gli::FORMAT_R_ATI1N_SNORM_BLOCK8: return vk::Format::eBc4SnormBlock;
            case gli::FORMAT_RG_ATI2N_UNORM_BLOCK16: return vk::Format::eBc5UnormBlock;
            case gli::FORMAT_RG_ATI2N_SNORM_BLOCK16: return vk::Format::eBc5SnormBlock;
            case gli::FORMAT_RGB_BP_UFLOAT_BLOCK16: return vk::Format::eBc6HUfloatBlock;
            case gli::FORMAT_RGB_BP_SFLOAT_BLOCK16: return vk::Format::eBc6HSfloatBlock;
            case gli::FORMAT_RGBA_BP_UNORM_BLOCK16: return vk::Format::eBc7UnormBlock;
            case gli::FORMAT_RGBA_BP_SRGB_BLOCK16: return vk::Format::eBc7SrgbBlock;
            case gli::FORMAT_RGB_ETC2_UNORM_BLOCK8: return vk::Format::eEtc2R8G8B8UnormBlock;
            case gli::FORMAT_RGB_ETC2_SRGB_BLOCK8: return vk::Format::eEtc2R8G8B8SrgbBlock;
            case gli::FORMAT_RGBA_ETC2_UNORM_BLOCK8: return vk::Format::eEtc2R8G8B8A1UnormBlock;
            case gli::FORMAT_RGBA_ETC2_SRGB_BLOCK8: return vk::Format::eEtc2R8G8B8A1SrgbBlock;
            case gli::FORMAT_RGBA_ETC2_UNORM_BLOCK16: return vk::Format::eEtc2R8G8B8A8UnormBlock;
            case gli::FORMAT_RGBA_ETC2_SRGB_BLOCK16: return vk::Format::eEtc2R8G8B8A8SrgbBlock;
            case gli::FORMAT_R_EAC_UNORM_BLOCK8: return vk::Format::eEacR11UnormBlock;
            case gli::FORMAT_R_EAC_SNORM_BLOCK8: return vk::Format::eEacR11SnormBlock;
            case gli::FORMAT_RG_EAC_UNORM_BLOCK16: return vk::Format::eEacR11G11UnormBlock;
            case gli::FORMAT_RG_EAC_SNORM_BLOCK16: return vk::Format::eEacR11G11SnormBlock;
            case gli::FORMAT_RGBA_ASTC_4X4_UNORM_BLOCK16: return vk::Format::eAstc4x4UnormBlock;
            case gli::FORMAT_RGBA_ASTC_4X4_SRGB_BLOCK16: return vk::Format::eAstc4x4SrgbBlock;
            case gli::FORMAT_RGBA_ASTC_5X4_UNORM_BLOCK16: return vk::Format::eAstc5x4UnormBlock;
            case gli::FORMAT_RGBA_ASTC_5X4_SRGB_BLOCK16: return vk::Format::eAstc5x4SrgbBlock;
            case gli::FORMAT_RGBA_ASTC_5X5_UNORM_BLOCK16: return vk::Format::eAstc5x5UnormBlock;
            case gli::FORMAT_RGBA_ASTC_5X5_SRGB_BLOCK16: return vk::Format::eAstc5x5SrgbBlock;
            case gli::FORMAT_RGBA_ASTC_6X5_UNORM_BLOCK16: return vk::Format::eAstc6x5UnormBlock;
            case gli::FORMAT_RGBA_ASTC_6X5_SRGB_BLOCK16: return vk::Format::eAstc6x5SrgbBlock;
            case gli::FORMAT_RGBA_ASTC_6X6_UNORM_BLOCK16: return vk::Format::eAstc6x6UnormBlock;
            case gli::FORMAT_RGBA_ASTC_6X6_SRGB_BLOCK16: return vk::Format::eAstc6x6SrgbBlock;
            case gli::FORMAT_RGBA_ASTC_8X5_UNORM_BLOCK16: return vk::Format::eAstc8x5UnormBlock;
            case gli::FORMAT_RGBA_ASTC_8X5_SRGB_BLOCK16: return vk::Format::eAstc8x5SrgbBlock;
            case gli::FORMAT_RGBA_ASTC_8X6_UNORM_BLOCK16: return vk::Format::eAstc8x6UnormBlock;
            case gli::FORMAT_RGBA_ASTC_8X6_SRGB_BLOCK16: return vk::Format::eAstc8x6SrgbBlock;
            case gli::FORMAT_RGBA_ASTC_8X8_UNORM_BLOCK16: return vk::Format::eAstc8x8UnormBlock;
            case gli::FORMAT_RGBA_ASTC_8X8_SRGB_BLOCK16: return vk::Format::eAstc8x8SrgbBlock;
            case gli::FORMAT_RGBA_ASTC_10X5_UNORM_BLOCK16: return vk::Format::eAstc10x5UnormBlock;
            case gli::FORMAT_RGBA_ASTC_10X5_SRGB_BLOCK16: return vk::Format::eAstc10x5SrgbBlock;
            case gli::FORMAT_RGBA_ASTC_10X6_UNORM_BLOCK16: return vk::Format::eAstc10x6UnormBlock;
            case gli::FORMAT_RGBA_ASTC_10X6_SRGB_BLOCK16: return vk::Format::eAstc10x6SrgbBlock;
            case gli::FORMAT_RGBA_ASTC_10X8_UNORM_BLOCK16: return vk::Format::eAstc10x8UnormBlock;
            case gli::FORMAT_RGBA_ASTC_10X8_SRGB_BLOCK16: return vk::Format::eAstc10x8SrgbBlock;
            case gli::FORMAT_RGBA_ASTC_10X10_UNORM_BLOCK16: return vk::Format::eAstc10x10UnormBlock;
            case gli::FORMAT_RGBA_ASTC_10X10_SRGB_BLOCK16: return vk::Format::eAstc10x10SrgbBlock;
            case gli::FORMAT_RGBA_ASTC_12X10_UNORM_BLOCK16: return vk::Format::eAstc12x10UnormBlock;
            case gli::FORMAT_RGBA_ASTC_12X10_SRGB_BLOCK16: return vk::Format::eAstc12x10SrgbBlock;
            case gli::FORMAT_RGBA_ASTC_12X12_UNORM_BLOCK16: return vk::Format::eAstc12x12UnormBlock;
            case gli::FORMAT_RGBA_ASTC_12X12_SRGB_BLOCK16: return vk::Format::eAstc12x12SrgbBlock;
            default:std::stringstream error;
                error << "The following GLI Format not supported (" << p_format << ")";
                throw std::runtime_error(error.str());
                break;
        }
    }

    vk::Image const& const Texture::getImage()
    {
        return m_image;
    }

    vk::Extent2D const& const Texture::getSize()
    {
        return m_imageInfo.size;
    }

    vk::DescriptorImageInfo const& const Texture::getImageDescriptor()
    {
        return m_descriptorImageInfo;
    }
}

