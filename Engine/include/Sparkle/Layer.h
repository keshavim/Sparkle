//
// Created by overlord on 6/27/25.
//

#ifndef LAYER_H
#define LAYER_H

#include <string>

namespace Sparkle {
    class Event; // Forward declaration

    // Base class for all layers (game, UI, ImGui, etc.)
    class Layer {
    public:
        explicit Layer(const std::string &name = "Layer") : m_name(name) {
        }

        virtual ~Layer() = default;

        virtual void on_attach() {
        }

        virtual void on_detach() {
        }

        virtual void on_update(float dt) {
        }

        virtual void on_event(Event &event) {
        }

        const std::string &name() const { return m_name; }

    protected:
        std::string m_name;
    };
}

#endif //LAYER_H
