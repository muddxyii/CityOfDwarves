//
// Created by muddxyii on 8/17/24.
//

#include "Engine.h"

Engine::Engine(const std::string &windowTitle, int windowWidth, int windowHeight) {
    windowSize.x = static_cast<float>(windowWidth);
    windowSize.y = static_cast<float>(windowHeight);

    if (SDL_Init(SDL_INIT_VIDEO)) {
        SDL_Log("SDL_Init failed: %s\n", SDL_GetError());
        exit(1);
    }

    window = SDL_CreateWindow(windowTitle.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                              windowWidth, windowHeight, SDL_WINDOW_SHOWN);
    if (!window) {
        SDL_Log("SDL_CreateWindow failed: %s\n", SDL_GetError());
        exit(1);
    }

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (!renderer) {
        SDL_Log("SDL_CreateRenderer failed: %s\n", SDL_GetError());
        exit(1);
    }

    // Init SDL2_image
    constexpr int imgFlags = IMG_INIT_PNG;
    if (!(IMG_Init(imgFlags) & imgFlags)) {
        // Handle SDL2_image initialization error
        SDL_Log("SDL2_image could not initialize! SDL2_image Error: %s\n", IMG_GetError());
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
    for (const auto& pair : textureManager.textures) {
        SDL_DestroyTexture(pair.second);
    }
    textureManager.textures.clear();
    IMG_Quit();
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

void Engine::setCurrentCamera(Camera* newCamera) {
    camera = newCamera;
}

void Engine::clearBackground() const {
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255); // Black background
    SDL_RenderClear(renderer);
}

void Engine::clearBackground(const Uint8 r, const Uint8 g, const Uint8 b) const {
    SDL_SetRenderDrawColor(renderer, r, g, b, 255);
    SDL_RenderClear(renderer);
}

int Engine::loadTexture(const std::string &path) {
    SDL_Texture* newTexture = IMG_LoadTexture(renderer, path.c_str());
    if (newTexture == nullptr) {
        SDL_Log("Unable to load image %s! SDL2_image Error: %s\n", path.c_str(), IMG_GetError());
        return -1;
    }

    const int textureId = textureManager.nextTextureId++;
    textureManager.textures[textureId] = newTexture;
    return textureId;
}

bool Engine::unloadTexture(const int textureId) {
    auto iterator = textureManager.textures.find(textureId);
    if (iterator == textureManager.textures.end()) {
        SDL_Log("Texture with ID %d does not exist", textureId);
        return false;
    }

    SDL_DestroyTexture(iterator->second);
    textureManager.textures.erase(iterator);

    SDL_Log("Texture with ID %d successfully unloaded", textureId);
    return true;
}

void Engine::drawRect(SDL_Rect rectToDraw) const {
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255); // white
    if (camera) {
        rectToDraw.x -= static_cast<int>(camera->getPosition().x);
        rectToDraw.y -= static_cast<int>(camera->getPosition().y);
    }
    SDL_RenderFillRect(renderer, &rectToDraw);
}

void Engine::drawTextureRect(SDL_Rect destRect, int textureId) const {
    const auto iterator = textureManager.textures.find(textureId);
    if (iterator == textureManager.textures.end()) {
        SDL_Log("Texture does not exist: %s\n", SDL_GetError());
        return;
    }
    if (camera) {
        destRect.x -= static_cast<int>(camera->getPosition().x);
        destRect.y -= static_cast<int>(camera->getPosition().y);
    }
    SDL_RenderCopy(renderer, iterator->second, nullptr, &destRect);
}

void Engine::drawTextureRectPro(SDL_Rect srcRect, SDL_Rect destRect, int textureId) const {
    const auto iterator = textureManager.textures.find(textureId);
    if (iterator == textureManager.textures.end()) {
        SDL_Log("Texture does not exist: %s\n", SDL_GetError());
        return;
    }
    if (camera) {
        destRect.x -= static_cast<int>(camera->getPosition().x);
        destRect.y -= static_cast<int>(camera->getPosition().y);
    }
    SDL_RenderCopy(renderer, iterator->second, nullptr, &destRect);
}

void Engine::presentRender() const {
    SDL_RenderPresent(renderer);
}
