//
// Created by muddxyii on 8/17/24.
//

#ifndef ENGINE_H
#define ENGINE_H

#include <SDL2/SDL.h>
#include <glm/glm.hpp>
#include "Input/Input.h"

class Engine {
public:
    Engine(int windowWidth, int windowHeight);
    ~Engine();

    [[nodiscard]] bool isKeyPressed(SDL_Scancode key) const;

    bool windowShouldClose();
    void clearBackground() const;
    void presentRender() const;
private:
    SDL_Window* window = nullptr;
    SDL_Renderer* renderer = nullptr;
    Input input = Input();
    glm::vec2 windowSize = glm::vec2(800, 600);
};



#endif //ENGINE_H
