//
// Created by overlord on 6/27/25.
//
#include "pch.h"
#include "Sparkle/engine.h"
#include "Sparkle/imguilayer.h"
#include "imgui.h"
#include "backends/imgui_impl_sdl3.h"
#include "backends/imgui_impl_vulkan.h"
#include <SDL3/SDL.h>
#include <SDL3/SDL_vulkan.h>

#include "Sparkle/log.h"


namespace Sparkle {
    ImGuiLayer::ImGuiLayer() : Layer("ImGuiLayer") {
    }

    ImGuiLayer::~ImGuiLayer() {
    }

    void ImGuiLayer::on_attach() {
        VulkanContext &ctx = Engine::Get().get_context();
        SDL_Window *window = Engine::Get().get_window().get_sdl_window();

        // 1. Create ImGui context
        IMGUI_CHECKVERSION();
        ImGui::CreateContext();
        ImGuiIO &io = ImGui::GetIO();
        (void) io;
        io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls

        // 2. Style
        ImGui::StyleColorsDark();

        // 3. Initialize SDL3 backend
        ImGui_ImplSDL3_InitForVulkan(window);

        // 4. Initialize Vulkan backend
        ImGui_ImplVulkan_InitInfo init_info = {};
        init_info.Instance = ctx.instance;
        init_info.PhysicalDevice = ctx.physicalDevice;
        init_info.Device = ctx.device;
        init_info.QueueFamily = ctx.graphicsQueueFamily;
        init_info.Queue = ctx.graphicsQueue;
        init_info.PipelineCache = ctx.pipelineCache;
        init_info.DescriptorPool = ctx.descriptorPool;
        init_info.Subpass = 0;
        init_info.RenderPass = ctx.renderPass;
        init_info.MinImageCount = ctx.imageCount;
        init_info.ImageCount = ctx.imageCount;
        init_info.MSAASamples = VK_SAMPLE_COUNT_1_BIT;
        init_info.Allocator = nullptr;
        init_info.CheckVkResultFn = [](VkResult err) {
            if (err != VK_SUCCESS) {
                fprintf(stderr, "Vulkan error: %d\n", err);
            }
        };

        ImGui_ImplVulkan_Init(&init_info);
    }


    void ImGuiLayer::on_detach() {
        ImGui_ImplVulkan_Shutdown();
        ImGui_ImplSDL3_Shutdown();
        ImGui::DestroyContext();
    }

    void ImGuiLayer::on_update(float dt) {
        // 1. Start SDL and Vulkan ImGui frame

        ImGui_ImplVulkan_NewFrame();
        ImGui_ImplSDL3_NewFrame();
        ImGui::NewFrame();

        // 2. Build your UI here
        ImGui::Begin("Demo");
        ImGui::Text("Hello, Vulkan + SDL3 + ImGui!");
        ImGui::Text("Time: %.3f", dt);
        ImGui::End();

        // 3. End frame (rendering happens later)
        ImGui::EndFrame();
        ImGui::Render();
    }


    void ImGuiLayer::on_event(Event &event) {
        // Forward SDL events to ImGui if needed
        // ImGui_ImplSDL3_ProcessEvent(&sdl_event);
    }
} // namespace Sparkle
