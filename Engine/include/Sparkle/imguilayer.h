//
// Created by overlord on 6/27/25.
//

#ifndef IMGUILAYER_H
#define IMGUILAYER_H

#include "Sparkle/layer.h"

namespace Sparkle {
    class ImGuiLayer : public Layer {
    public:
        ImGuiLayer();
        ~ImGuiLayer() override;

        void on_attach() override;
        void on_detach() override;
        void on_update(float dt) override;
        void on_event(Event& event) override;
    };
}
#endif //IMGUILAYER_H
