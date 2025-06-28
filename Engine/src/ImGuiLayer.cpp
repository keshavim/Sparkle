//
// Created by overlord on 6/27/25.
//
#include "skpch.h"
#include "Sparkle/Engine.h"
#include "Sparkle/ImGuiLayer.h"
#include "imgui.h"
#include "backends/imgui_impl_sdl3.h"
#include "backends/imgui_impl_vulkan.h"
#include <SDL3/SDL.h>
#include <SDL3/SDL_vulkan.h>

#include "Sparkle/Log.h"


namespace Sparkle {
    ImGuiLayer::ImGuiLayer() : Layer("ImGuiLayer") {
    }

    ImGuiLayer::~ImGuiLayer() {
    }

    void ImGuiLayer::on_attach() {

    }


    void ImGuiLayer::on_detach() {

    }

    void ImGuiLayer::on_update(float dt) {

    }


    void ImGuiLayer::on_event(Event &event) {
        // Forward SDL events to ImGui if needed
        // ImGui_ImplSDL3_ProcessEvent(&sdl_event);
    }
} // namespace Sparkle
