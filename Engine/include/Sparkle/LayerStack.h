//
// Created by overlord on 6/27/25.
//

#ifndef LAYER_STACK_H
#define LAYER_STACK_H

#include <vector>
#include <memory>
#include "Sparkle/Layer.h"

namespace Sparkle {
    // LayerStack manages layers and overlays.
    // Layers are updated/rendered in order; overlays are always on top.
    class LayerStack {
    public:
        LayerStack();

        ~LayerStack();

        // Push a layer (insert before overlays)
        void push_layer(Layer *layer);

        // Push an overlay (always at the end)
        void push_overlay(Layer *overlay);

        // Remove a layer or overlay (searches whole stack)
        void remove_layer(Layer *layer);

        // Call on_update for all layers and overlays
        void on_update(float dt) const;

        //call on_render on oll layer and overlays
        void on_render() const;

        // Call on_event for all layers and overlays (from top to bottom)
        void on_event(Event &event);

        // Remove all layers and overlays
        void clear();

        // Iterators for custom usage
        auto begin() { return m_layers.begin(); }
        auto end() { return m_layers.end(); }

    private:
        std::vector<Layer *> m_layers;
        size_t m_overlay_index = 0; // Index where overlays start
    };
}
#endif //LAYER_STACK_H
