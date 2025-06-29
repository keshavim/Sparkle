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

        //temporery
        ImGui_ImplVulkanH_Window mainWindowData;

    };
    class Renderer {
    public:
        void Init();
        void Cleanup();
        void Render();

        VulkanContext &getContext() {return m_Context;}


        static void check_vk_result(VkResult err);

    private:
        //need to clean up these functions
        //still useing elements form example
        static bool IsExtensionAvailable(const ImVector<VkExtensionProperties> &properties, const char *extension);
        void SetupVulkan(ImVector<const char *> instance_extensions);


        void FrameRender(ImGui_ImplVulkanH_Window *wd, ImDrawData *draw_data);
        void FramePresent(ImGui_ImplVulkanH_Window *wd);

        void CleanupVulkan();

        //this part will move to imgui layer
        void SetupVulkanWindow(ImGui_ImplVulkanH_Window *wd, VkSurfaceKHR surface, int width, int height);
        void CleanupVulkanWindow();


    private:
        VulkanContext m_Context;




    };
}


#endif //RENDERER_H
