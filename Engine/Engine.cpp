//
// Created by muddxyii on 8/17/24.
//

#include "Engine.h"

Engine::Engine(const std::string &windowTitle, int windowWidth, int windowHeight) {
    windowSize.x = static_cast<float>(windowWidth);
    windowSize.y = static_cast<float>(windowHeight);

    if (SDL_Init(SDL_INIT_VIDEO)) {
        SDL_Log("SDL_Init failed: %s", SDL_GetError());
        exit(1);
    }

    window = SDL_CreateWindow(windowTitle.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                              windowWidth, windowHeight, SDL_WINDOW_SHOWN);
    if (!window) {
        SDL_Log("SDL_CreateWindow failed: %s", SDL_GetError());
        exit(1);
    }

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (!renderer) {
        SDL_Log("SDL_CreateRenderer failed: %s", SDL_GetError());
        exit(1);
    }
}

Engine::~Engine() {
    if (renderer != nullptr) {
        SDL_DestroyRenderer(renderer);
        renderer = nullptr;
    }
    if (window != nullptr) {
        SDL_DestroyWindow(window);
        window = nullptr;
    }
    SDL_Quit();
}

bool Engine::isKeyPressed(const SDL_Scancode key) const {
    return input.getKeyStatus(key);
}

bool Engine::windowShouldClose() {
    return input.pollEvents();
}

void Engine::setTargetFPS(const float fps) {
    frameRateController.targetFPS = fps;
}

void Engine::limitFrameRate() {
    frameRateController.frameDelay = static_cast<int>(1000.0f / frameRateController.targetFPS);
    frameRateController.frameStart = SDL_GetTicks();
}

void Engine::capFrameRate() {
    frameRateController.frameTime = static_cast<int>(SDL_GetTicks() - frameRateController.frameStart);
    if (frameRateController.frameDelay > frameRateController.frameTime) {
        SDL_Delay(frameRateController.frameDelay - frameRateController.frameTime);
    }
}

float Engine::getDeltaTime() const {
    return static_cast<float>(frameRateController.frameTime) / 1000.0f;
}

void Engine::clearBackground() const {
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255); // Black background
    SDL_RenderClear(renderer);
}

void Engine::clearBackground(const Uint8 r, const Uint8 g, const Uint8 b) const {
    SDL_SetRenderDrawColor(renderer, r, g, b, 255);
    SDL_RenderClear(renderer);
}

void Engine::presentRender() const {
    SDL_RenderPresent(renderer);
}
