//
// Created by overlord on 6/27/25.
//
#include "skpch.h"
#include "Sparkle/LayerStack.h"

#include "Sparkle/Events.h"

namespace Sparkle {
    LayerStack::LayerStack() = default;

    LayerStack::~LayerStack() {
        clear();
    }

    void LayerStack::push_layer(Layer *layer) {
        m_layers.insert(m_layers.begin() + m_overlay_index, layer);
        ++m_overlay_index;
        layer->on_attach();
    }

    void LayerStack::push_overlay(Layer *overlay) {
        m_layers.push_back(overlay);
        overlay->on_attach();
    }

    void LayerStack::remove_layer(Layer *layer) {
        auto it = std::find(m_layers.begin(), m_layers.end(), layer);
        if (it != m_layers.end()) {
            // Call on_detach before removing
            (*it)->on_detach();
            // Adjust overlay index if removing a non-overlay
            if (std::distance(m_layers.begin(), it) < static_cast<ptrdiff_t>(m_overlay_index)) {
                --m_overlay_index;
            }
        }
    }

    void LayerStack::on_update(float dt) const {
        for (auto &layer: m_layers)
            layer->on_update(dt);
    }

    void LayerStack::on_event(Event &event) {
        //update from top to bottom
        for (auto it = m_layers.rbegin(); it != m_layers.rend(); ++it) {
            (*it)->on_event(event);
            if (event.handled) {
                break;
            }
        }
    }

    void LayerStack::clear() {
        for (auto &layer: m_layers)
            layer->on_detach();
        m_layers.clear();
        m_overlay_index = 0;
    }
}
