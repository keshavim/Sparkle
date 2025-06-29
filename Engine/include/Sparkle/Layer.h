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

        //called when layer is added to the stack
        //used for init
        virtual void on_attach() {
        }
        //called when removed from stack
        virtual void on_detach() {
        }
        //used for handeling events, called first in loop
        virtual void on_event(Event &event) {
        }


        //used for updateing logic in the layer. called second in loop
        virtual void on_update(float dt) {
        }

        //used for rendering, called third in loop
        virtual void on_render() {

        }


        const std::string &name() const { return m_name; }

    protected:
        std::string m_name;
    };
}

#endif //LAYER_H
