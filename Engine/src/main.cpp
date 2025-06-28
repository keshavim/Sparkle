
#include "pch.h"
#include "Sparkle.h"


class ExampleLayer : public Sparkle::Layer {
public:
    ExampleLayer() : Layer("Example Layer") {
    }

    void on_update(f32 delta_time) override {
    }

    void on_event(Sparkle::Event &e) override {

    }
};


class TestGame final : public Sparkle::Engine {
public:
    TestGame() {

    }

    ~TestGame() override = default;
};

int main() {
    TestGame game;
    game.run();
    return 0;
}
