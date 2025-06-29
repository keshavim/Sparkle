//
// Created by overlord on 6/27/25.
//

#ifndef IMGUILAYER_H
#define IMGUILAYER_H

#include "Sparkle/Layer.h"

namespace Sparkle {
    class ImGuiLayer : public Layer {
    public:
        ImGuiLayer();
        ~ImGuiLayer() override;

        void on_attach() override;
        void on_detach() override;
        void on_update(float dt) override;
        void on_event(Event& event) override;
    private:
        ImGui_ImplVulkanH_Window mainWindowData;
        // Our state
        bool show_demo_window = true;
        bool show_another_window = false;
        ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);


        void SetupVulkanWindow();
        void FrameRender(ImDrawData *draw_data);
        void FramePresent();

    };
}
#endif //IMGUILAYER_H
