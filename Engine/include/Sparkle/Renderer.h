//
// Created by overlord on 6/28/25.
//

#ifndef RENDERER_H
#define RENDERER_H

#include "Sparkle/Base.h"
#include "vulkan/vulkan.h"
#include "SDL3/SDL.h"
#include <SDL3/SDL_vulkan.h>

//these will be moved later ________________---------------------------------------
#include "imgui.h"
#include "imgui_impl_sdl3.h"
#include "imgui_impl_vulkan.h"

namespace Sparkle {
    struct VulkanContext {
        VkAllocationCallbacks *allocator = nullptr;
        VkInstance instance = VK_NULL_HANDLE;
        VkPhysicalDevice physicalDevice = VK_NULL_HANDLE;
        VkDevice device = VK_NULL_HANDLE;
        uint32_t queueFamily = (u32) -1;
        VkQueue queue = VK_NULL_HANDLE;
        VkPipelineCache pipelineCache = VK_NULL_HANDLE;
        VkDescriptorPool descriptorPool = VK_NULL_HANDLE;
        uint32_t minImageCount = 2;
        bool swapChainRebuild = false;

    };
    class Renderer {
    public:
        void Init();
        void Cleanup();
        void Render();

        VulkanContext &getContext() {return m_Context;}

        //static function for checking vulken errors
        static void check_vk_result(VkResult err);

    private:
        //vulken specific
        static bool IsExtensionAvailable(const ImVector<VkExtensionProperties> &properties, const char *extension);
        void SetupVulkan(ImVector<const char *> instance_extensions);
        void CleanupVulkan();

    private:
        VulkanContext m_Context;




    };
}


#endif //RENDERER_H
