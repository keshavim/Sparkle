#include <SDL3/SDL.h>
#include <iostream>
int main() {
    if (!SDL_Init(SDL_INIT_VIDEO)) {
        std::cerr << "SDL_Init Error: " << SDL_GetError() << std::endl;
        return 1;
    }
    SDL_Quit();

    std::cout << "SDL3 initialized successfully!" << std::endl;
    return 0;
}
