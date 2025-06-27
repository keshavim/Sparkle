
#include "pch.h"
#include "engine.h"
#include "log.h"

class TestGame final : public Sparkle::Engine {
public:
    TestGame() = default;
    ~TestGame() override = default;

protected:
    void on_update(f32 delta_time) override {
        // Game logic goes here
        LOG_INFO("testgame update, delta_time: {}", delta_time);
    }
};

int main() {
    TestGame game;
    game.run();
    return 0;
}
