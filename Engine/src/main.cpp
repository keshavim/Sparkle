#include "base.h"
#include "log.h"
#include <SDL3/SDL.h>
int main() {
    constexpr i32 counter = 42;
    constexpr i32 numbers[] = {1, 2, 3, 4};
    LOG_TRACE("Counter {}, Array size: {}\n", counter, std::size(numbers));

    LOG_INFO("Engine started!\n");
    if (!SDL_Init(SDL_INIT_VIDEO)) {
        LOG_ERROR("SDL_Init Error: {}", SDL_GetError());
        return 1;
    }
    SDL_Quit();

    LOG_TRACE("SDL3 initialized successfully!\n");
    return 0;
}
