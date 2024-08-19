//
// Created by muddxyii on 8/17/24.
//

#ifndef ENGINE_H
#define ENGINE_H

#include <string>
#include <string>
#include <unordered_map>
#include <glm/glm.hpp>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "Camera/Camera.h"
#include "Input/Input.h"

struct FrameRateController {
    float targetFPS = 60.0f;
    Uint32 frameStart;
    int frameDelay;
    int frameTime;
};

struct TextureManager {
    std::unordered_map<int, SDL_Texture*> textures = {};
    int nextTextureId = 0;
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

    void setCurrentCamera(Camera* newCamera);
    void clearBackground() const;
    void clearBackground(Uint8 r, Uint8 g, Uint8 b) const;

    int loadTexture(const std::string& path);
    void drawRect(SDL_Rect rectToDraw) const;
    void drawTextureRect(SDL_Rect destRect, int textureId) const;

    void presentRender() const;
private:
    SDL_Window* window = nullptr;
    SDL_Renderer* renderer = nullptr;
    glm::vec2 windowSize = glm::vec2(800, 600);

    Camera* camera = nullptr;

    Input input = Input();

    FrameRateController frameRateController = {};
    TextureManager textureManager = {};;
};



#endif //ENGINE_H
