//
// Created by overlord on 6/27/25.
//

#ifndef IMGUILAYER_H
#define IMGUILAYER_H

#include "Sparkle/Layer.h"

namespace Sparkle {
    class ImGuiLayer : public Layer {
    public:
        ImGuiLayer(bool show_demo, bool show_another_window, ImVec4 clear_color);
        ~ImGuiLayer() override;

        void on_attach() override;
        void on_detach() override;
        void on_render() override;
        void on_update(float dt) override;
        void on_event(Event& event) override;

        void set_show_demo_window(bool show_demo_window) {
            this->show_demo_window = show_demo_window;
        }

        void set_show_another_window(bool show_another_window) {
            this->show_another_window = show_another_window;
        }

        void set_clear_color(const ImVec4 &clear_color) {
            this->clear_color = clear_color;
        }
    private:
        ImGui_ImplVulkanH_Window mainWindowData;
        // Our state
        bool show_demo_window;
        bool show_another_window;
        ImVec4 clear_color;


        void SetupVulkanWindow();
        void FrameRender(ImDrawData *draw_data);
        void FramePresent();

        ImVec2 m_MousePos = ImVec2(-FLT_MAX, -FLT_MAX);
        bool m_MouseDown[5] = { false, false, false, false, false };
        float m_MouseWheel = 0.0f;
        float m_MouseWheelH = 0.0f;

    };
}
#endif //IMGUILAYER_H
