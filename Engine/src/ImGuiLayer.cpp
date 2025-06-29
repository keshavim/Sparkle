//
// Created by overlord on 6/27/25.
//
#include "skpch.h"
#include "Sparkle/Engine.h"
#include "Sparkle/ImGuiLayer.h"

#include <imgui.h>
#include <backends/imgui_impl_sdl3.h>
#include <backends/imgui_impl_vulkan.h>
#include <SDL3/SDL.h>
#include <SDL3/SDL_vulkan.h>

#include "Sparkle/Log.h"

namespace Sparkle {
    ImGuiLayer::ImGuiLayer(bool show_demo, bool show_another_window, ImVec4 clear_color)
        : Layer("ImGuiLayer"),
          show_demo_window(show_demo),
          show_another_window(show_another_window),
          clear_color(clear_color) {
        SetupVulkanWindow();
    }

    ImGuiLayer::~ImGuiLayer() {
    }

    void ImGuiLayer::on_attach() {
        const VulkanContext &m_Context = Engine::Get().get_renderer().getContext();
        SDL_Window *window = Engine::Get().get_window().GetSDLWindow();

        // Setup Dear ImGui context
        IMGUI_CHECKVERSION();
        ImGui::CreateContext();
        ImGuiIO &io = ImGui::GetIO();
        (void) io;
        io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard; // Enable Keyboard Controls
        io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad; // Enable Gamepad Controls
        io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;
        io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;


        // Setup Dear ImGui style
        ImGui::StyleColorsDark();
        //ImGui::StyleColorsLight();

        // Setup scaling
        ImGuiStyle &style = ImGui::GetStyle();
        style.ScaleAllSizes(Engine::Get().get_window().GetScale());
        // Bake a fixed style scale. (until we have a solution for dynamic style scaling, changing this requires resetting Style + calling this again)
        style.FontScaleDpi = Engine::Get().get_window().GetScale();
        // Set initial font scale. (using io.ConfigDpiScaleFonts=true makes this unnecessary. We leave both here for documentation purpose)

        // Setup Platform/Renderer backends
        ImGui_ImplSDL3_InitForVulkan(window);
        ImGui_ImplVulkan_InitInfo init_info = {};
        //init_info.ApiVersion = VK_API_VERSION_1_3;              // Pass in your value of VkApplicationInfo::apiVersion, otherwise will default to header version.
        init_info.Instance = m_Context.instance;
        init_info.PhysicalDevice = m_Context.physicalDevice;
        init_info.Device = m_Context.device;
        init_info.QueueFamily = m_Context.queueFamily;
        init_info.Queue = m_Context.queue;
        init_info.PipelineCache = m_Context.pipelineCache;
        init_info.DescriptorPool = m_Context.descriptorPool;
        init_info.RenderPass = mainWindowData.RenderPass;
        init_info.Subpass = 0;
        init_info.MinImageCount = m_Context.minImageCount;
        init_info.ImageCount = mainWindowData.ImageCount;
        init_info.MSAASamples = VK_SAMPLE_COUNT_1_BIT;
        init_info.Allocator = m_Context.allocator;
        init_info.CheckVkResultFn = Renderer::check_vk_result;
        ImGui_ImplVulkan_Init(&init_info);

        // Load Fonts
        // - If no fonts are loaded, dear imgui will use the default font. You can also load multiple fonts and use ImGui::PushFont()/PopFont() to select them.
        // - AddFontFromFileTTF() will return the ImFont* so you can store it if you need to select the font among multiple.
        // - If the file cannot be loaded, the function will return a nullptr. Please handle those errors in your application (e.g. use an assertion, or display an error and quit).
        // - Use '#define IMGUI_ENABLE_FREETYPE' in your imconfig file to use Freetype for higher quality font rendering.
        // - Read 'docs/FONTS.md' for more instructions and details.
        // - Remember that in C/C++ if you want to include a backslash \ in a string literal you need to write a double backslash \\ !
        //style.FontSizeBase = 20.0f;
        //io.Fonts->AddFontDefault();
        //io.Fonts->AddFontFromFileTTF("c:\\Windows\\Fonts\\segoeui.ttf");
        //io.Fonts->AddFontFromFileTTF("../../misc/fonts/DroidSans.ttf");
        //io.Fonts->AddFontFromFileTTF("../../misc/fonts/Roboto-Medium.ttf");
        //io.Fonts->AddFontFromFileTTF("../../misc/fonts/Cousine-Regular.ttf");
        //ImFont* font = io.Fonts->AddFontFromFileTTF("c:\\Windows\\Fonts\\ArialUni.ttf");
        //IM_ASSERT(font != nullptr);
    }


    void ImGuiLayer::on_detach() {
        const VulkanContext &m_Context = Engine::Get().get_renderer().getContext();
        ImGui_ImplVulkanH_DestroyWindow(m_Context.instance, m_Context.device, &mainWindowData,
                                        m_Context.allocator);

        ImGui_ImplVulkan_Shutdown();
        ImGui_ImplSDL3_Shutdown();
        ImGui::DestroyContext();
    }

    void ImGuiLayer::on_update(float dt) {
        VulkanContext &m_Context = Engine::Get().get_renderer().getContext();
        SDL_Window *window = Engine::Get().get_window().GetSDLWindow();


        // Resize swap chain?
        int fb_width, fb_height;
        SDL_GetWindowSize(window, &fb_width, &fb_height);
        if (fb_width > 0 && fb_height > 0 && (
                m_Context.swapChainRebuild || mainWindowData.Width != fb_width || mainWindowData.
                Height != fb_height)) {
            ImGui_ImplVulkan_SetMinImageCount(m_Context.minImageCount);
            ImGui_ImplVulkanH_CreateOrResizeWindow(m_Context.instance, m_Context.physicalDevice, m_Context.device,
                                                   &mainWindowData,
                                                   m_Context.queueFamily, m_Context.allocator, fb_width, fb_height,
                                                   m_Context.minImageCount);
            mainWindowData.FrameIndex = 0;
            m_Context.swapChainRebuild = false;
        }

        // Start the Dear ImGui frame
        ImGui_ImplVulkan_NewFrame();
        ImGui_ImplSDL3_NewFrame();
        ImGui::NewFrame();

        // 1. Show the big demo window (Most of the sample code is in ImGui::ShowDemoWindow()! You can browse its code to learn more about Dear ImGui!).
        if (show_demo_window)
            ImGui::ShowDemoWindow(&show_demo_window);

        // 2. Show a simple window that we create ourselves. We use a Begin/End pair to create a named window.
        {
            static float f = 0.0f;
            static int counter = 0;

            ImGui::Begin("Hello, world!"); // Create a window called "Hello, world!" and append into it.

            ImGui::Text("This is some useful text."); // Display some text (you can use a format strings too)
            ImGui::Checkbox("Demo Window", &show_demo_window); // Edit bools storing our window open/close state
            ImGui::Checkbox("Another Window", &show_another_window);

            ImGui::SliderFloat("float", &f, 0.0f, 1.0f); // Edit 1 float using a slider from 0.0f to 1.0f
            ImGui::ColorEdit3("clear color", (float *) &clear_color); // Edit 3 floats representing a color

            if (ImGui::Button("Button"))
                // Buttons return true when clicked (most widgets return true when edited/activated)
                counter++;
            ImGui::SameLine();
            ImGui::Text("counter = %d", counter);
            ImGuiIO &io = ImGui::GetIO();
            ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / io.Framerate, io.Framerate);
            ImGui::End();
        }

        // 3. Show another simple window.
        if (show_another_window) {
            ImGui::Begin("Another Window", &show_another_window);
            // Pass a pointer to our bool variable (the window will have a closing button that will clear the bool when clicked)
            ImGui::Text("Hello from another window!");
            if (ImGui::Button("Close Me"))
                show_another_window = false;
            ImGui::End();
        }
    }

    void ImGuiLayer::on_render() {
        ImGui::Render();
        ImDrawData *draw_data = ImGui::GetDrawData();
        const bool is_minimized = (draw_data->DisplaySize.x <= 0.0f || draw_data->DisplaySize.y <= 0.0f);
        ImGui_ImplVulkanH_Window *wd = &mainWindowData;
        if (!is_minimized) {
            wd->ClearValue.color.float32[0] = clear_color.x * clear_color.w;
            wd->ClearValue.color.float32[1] = clear_color.y * clear_color.w;
            wd->ClearValue.color.float32[2] = clear_color.z * clear_color.w;
            wd->ClearValue.color.float32[3] = clear_color.w;
            FrameRender(draw_data);
            FramePresent();
        }
    }


    void ImGuiLayer::on_event(Event &event) {

    }


    void ImGuiLayer::SetupVulkanWindow() {
        ImGui_ImplVulkanH_Window *wd = &mainWindowData;
        const VulkanContext &ctx = Engine::Get().get_renderer().getContext();
        SDL_Window *window = Engine::Get().get_window().GetSDLWindow();

        // Create Window Surface
        VkSurfaceKHR surface;
        VkResult err;
        if (SDL_Vulkan_CreateSurface(window, ctx.instance, ctx.allocator, &surface) == 0) {
            printf("Failed to create Vulkan surface.\n");
            return;
        }

        // Create Framebuffers
        int width, height;
        SDL_GetWindowSize(window, &width, &height);


        wd->Surface = surface;

        // Check for WSI support
        VkBool32 res;
        vkGetPhysicalDeviceSurfaceSupportKHR(ctx.physicalDevice, ctx.queueFamily, wd->Surface, &res);
        if (res != VK_TRUE) {
            fprintf(stderr, "Error no WSI support on physical device 0\n");
            exit(-1);
        }

        // Select Surface Format
        const VkFormat requestSurfaceImageFormat[] = {
            VK_FORMAT_B8G8R8A8_UNORM, VK_FORMAT_R8G8B8A8_UNORM, VK_FORMAT_B8G8R8_UNORM, VK_FORMAT_R8G8B8_UNORM
        };
        const VkColorSpaceKHR requestSurfaceColorSpace = VK_COLORSPACE_SRGB_NONLINEAR_KHR;
        wd->SurfaceFormat = ImGui_ImplVulkanH_SelectSurfaceFormat(ctx.physicalDevice, wd->Surface,
                                                                  requestSurfaceImageFormat,
                                                                  (size_t) IM_ARRAYSIZE(requestSurfaceImageFormat),
                                                                  requestSurfaceColorSpace);

        // Select Present Mode
#ifdef APP_USE_UNLIMITED_FRAME_RATE
        VkPresentModeKHR present_modes[] = { VK_PRESENT_MODE_MAILBOX_KHR, VK_PRESENT_MODE_IMMEDIATE_KHR, VK_PRESENT_MODE_FIFO_KHR };
#else
        VkPresentModeKHR present_modes[] = {VK_PRESENT_MODE_FIFO_KHR};
#endif
        wd->PresentMode = ImGui_ImplVulkanH_SelectPresentMode(ctx.physicalDevice, wd->Surface, &present_modes[0],
                                                              IM_ARRAYSIZE(present_modes));
        //printf("[vulkan] Selected PresentMode = %d\n", wd->PresentMode);

        // Create SwapChain, RenderPass, Framebuffer, etc.
        IM_ASSERT(ctx.minImageCount >= 2);
        ImGui_ImplVulkanH_CreateOrResizeWindow(ctx.instance, ctx.physicalDevice, ctx.device, wd,
                                               ctx.queueFamily, ctx.allocator,
                                               width, height, ctx.minImageCount);

        SDL_SetWindowPosition(window, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED);
        SDL_ShowWindow(window);
    }

    void ImGuiLayer::FrameRender(ImDrawData *draw_data) {
        VulkanContext &m_Context = Engine::Get().get_renderer().getContext();
        ImGui_ImplVulkanH_Window *wd = &mainWindowData;


        VkSemaphore image_acquired_semaphore = wd->FrameSemaphores[wd->SemaphoreIndex].ImageAcquiredSemaphore;
        VkSemaphore render_complete_semaphore = wd->FrameSemaphores[wd->SemaphoreIndex].RenderCompleteSemaphore;
        VkResult err = vkAcquireNextImageKHR(m_Context.device, wd->Swapchain, UINT64_MAX, image_acquired_semaphore,
                                             VK_NULL_HANDLE,
                                             &wd->FrameIndex);
        if (err == VK_ERROR_OUT_OF_DATE_KHR || err == VK_SUBOPTIMAL_KHR)
            m_Context.swapChainRebuild = true;
        if (err == VK_ERROR_OUT_OF_DATE_KHR)
            return;
        if (err != VK_SUBOPTIMAL_KHR)
            Renderer::check_vk_result(err);

        ImGui_ImplVulkanH_Frame *fd = &wd->Frames[wd->FrameIndex]; {
            err = vkWaitForFences(m_Context.device, 1, &fd->Fence, VK_TRUE, UINT64_MAX);
            // wait indefinitely instead of periodically checking
            Renderer::check_vk_result(err);

            err = vkResetFences(m_Context.device, 1, &fd->Fence);
            Renderer::check_vk_result(err);
        } {
            err = vkResetCommandPool(m_Context.device, fd->CommandPool, 0);
            Renderer::check_vk_result(err);
            VkCommandBufferBeginInfo info = {};
            info.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;
            info.flags |= VK_COMMAND_BUFFER_USAGE_ONE_TIME_SUBMIT_BIT;
            err = vkBeginCommandBuffer(fd->CommandBuffer, &info);
            Renderer::check_vk_result(err);
        } {
            VkRenderPassBeginInfo info = {};
            info.sType = VK_STRUCTURE_TYPE_RENDER_PASS_BEGIN_INFO;
            info.renderPass = wd->RenderPass;
            info.framebuffer = fd->Framebuffer;
            info.renderArea.extent.width = wd->Width;
            info.renderArea.extent.height = wd->Height;
            info.clearValueCount = 1;
            info.pClearValues = &wd->ClearValue;
            vkCmdBeginRenderPass(fd->CommandBuffer, &info, VK_SUBPASS_CONTENTS_INLINE);
        }

        // Record dear imgui primitives into command buffer
        ImGui_ImplVulkan_RenderDrawData(draw_data, fd->CommandBuffer);

        ImGui::UpdatePlatformWindows();
        ImGui::RenderPlatformWindowsDefault();

        // Submit command buffer
        vkCmdEndRenderPass(fd->CommandBuffer); {
            VkPipelineStageFlags wait_stage = VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT;
            VkSubmitInfo info = {};
            info.sType = VK_STRUCTURE_TYPE_SUBMIT_INFO;
            info.waitSemaphoreCount = 1;
            info.pWaitSemaphores = &image_acquired_semaphore;
            info.pWaitDstStageMask = &wait_stage;
            info.commandBufferCount = 1;
            info.pCommandBuffers = &fd->CommandBuffer;
            info.signalSemaphoreCount = 1;
            info.pSignalSemaphores = &render_complete_semaphore;

            err = vkEndCommandBuffer(fd->CommandBuffer);
            Renderer::check_vk_result(err);
            err = vkQueueSubmit(m_Context.queue, 1, &info, fd->Fence);
            Renderer::check_vk_result(err);
        }
    }

    void ImGuiLayer::FramePresent() {
        VulkanContext &m_Context = Engine::Get().get_renderer().getContext();
        ImGui_ImplVulkanH_Window *wd = &mainWindowData;


        if (m_Context.swapChainRebuild)
            return;
        VkSemaphore render_complete_semaphore = wd->FrameSemaphores[wd->SemaphoreIndex].RenderCompleteSemaphore;
        VkPresentInfoKHR info = {};
        info.sType = VK_STRUCTURE_TYPE_PRESENT_INFO_KHR;
        info.waitSemaphoreCount = 1;
        info.pWaitSemaphores = &render_complete_semaphore;
        info.swapchainCount = 1;
        info.pSwapchains = &wd->Swapchain;
        info.pImageIndices = &wd->FrameIndex;
        VkResult err = vkQueuePresentKHR(m_Context.queue, &info);
        if (err == VK_ERROR_OUT_OF_DATE_KHR || err == VK_SUBOPTIMAL_KHR)
            m_Context.swapChainRebuild = true;
        if (err == VK_ERROR_OUT_OF_DATE_KHR)
            return;
        if (err != VK_SUBOPTIMAL_KHR)
            Renderer::check_vk_result(err);
        wd->SemaphoreIndex = (wd->SemaphoreIndex + 1) % wd->SemaphoreCount; // Now we can use the next set of semaphores
    }
} // namespace Sparkle
