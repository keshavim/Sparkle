//
// Created by overlord on 6/26/25.
//

#ifndef ENGINE_H
#define ENGINE_H

#include "Sparkle/base.h"
#include "Sparkle/window.h"
#include "Sparkle/eventsystem.h"
#include "Sparkle/layer_stack.h"

#include "vulkan/vulkan.h"

namespace Sparkle {

    struct VulkanContext {
        VkInstance instance;
        VkSurfaceKHR surface;
        VkPhysicalDevice physicalDevice;
        VkDevice device;
        VkQueue graphicsQueue;
        uint32_t graphicsQueueFamily;

        VkSwapchainKHR swapchain;
        std::vector<VkImage> swapchainImages;
        std::vector<VkImageView> swapchainImageViews;
        std::vector<VkFramebuffer> framebuffers;
        VkExtent2D swapchainExtent;
        VkFormat swapchainImageFormat;

        VkRenderPass renderPass;
        VkCommandPool commandPool;
        std::vector<VkCommandBuffer> commandBuffers;
        VkSemaphore imageAvailableSemaphore;
        VkSemaphore renderFinishedSemaphore;
        VkFence inFlightFence;

        VkDescriptorPool descriptorPool;
        VkPipelineCache pipelineCache;

        uint32_t imageCount;
    };

    class Engine {
    public:
        // Get the singleton instance
        Engine();

        virtual ~Engine();

        // No copying or moving
        Engine(const Engine&) = delete;
        Engine& operator=(const Engine&) = delete;
        Engine(Engine&&) = delete;
        Engine& operator=(Engine&&) = delete;

        // Main entry point
        void run();

        void pushLayer(Layer *layer);

        void pushOverlay(Layer *layer);

        // Accessors for systems
        static Engine& Get() {return *s_instance;}
        Window& get_window() { return m_window; }

        VulkanContext &get_context() { return m_context; }


    private:
        void on_update(f32 delta_time);

        void on_event(Event &e);

        //create defaule callbacks for all events
        void register_events();

        bool init_vulkan();
        void render_frame();
        void cleanup_vulkan();

        Window m_window;
        EventSystem m_event_system;
        LayerStack m_layers;
        bool m_is_running;

        VulkanContext m_context;

        static Engine *s_instance;
    };
}
#endif //ENGINE_H
