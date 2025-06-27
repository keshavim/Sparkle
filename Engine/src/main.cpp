
#include "pch.h"
#include "Sparkle.h"


class ExampleLayer : public Sparkle::Layer {
public:
    ExampleLayer() : Layer("Example Layer") {
    }

    void on_update(f32 delta_time) override {
        //LOG_TRACE("Game Layer Update");
    }

    void on_event(Sparkle::Event &e) override {
        if (Input.is_key_pressed(Sparkle::Key::Shift)) {
            LOG_INFO("game event");
        }
    }
};


class TestGame final : public Sparkle::Engine {
public:
    TestGame() {
        pushLayer(new ExampleLayer());
    }

    ~TestGame() override = default;
};

int main() {
    TestGame game;
    game.run();
    return 0;
}
