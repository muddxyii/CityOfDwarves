//
// Created by muddxyii on 8/17/24.
//

#ifndef ENGINE_H
#define ENGINE_H

#include <string>
#include <SDL2/SDL.h>
#include <glm/glm.hpp>
#include "Input/Input.h"

struct FrameRateController {
    float targetFPS = 60.0f;
    Uint32 frameStart;
    int frameDelay;
    int frameTime;
};

class Engine {
public:
    Engine(const std::string &windowTitle, int windowWidth, int windowHeight);
    ~Engine();

    [[nodiscard]] bool isKeyPressed(SDL_Scancode key) const;

    bool windowShouldClose();

    void setTargetFPS(float fps);
    void limitFrameRate();
    void capFrameRate();

    float getDeltaTime() const;

    void clearBackground() const;
    void clearBackground(Uint8 r, Uint8 g, Uint8 b) const;
    void presentRender() const;
private:
    SDL_Window* window = nullptr;
    SDL_Renderer* renderer = nullptr;
    Input input = Input();
    glm::vec2 windowSize = glm::vec2(800, 600);
    FrameRateController frameRateController = {};
};



#endif //ENGINE_H
