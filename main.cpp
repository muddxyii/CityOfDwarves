#include <array>
#include <iostream>
#include <SDL2/SDL.h>
#include <glm/glm.hpp>
#include "Engine/Engine.h"

int main()
{
    Engine engine = Engine("City of Dwarves" ,800, 600);
    Camera camera = Camera();

    int grassId = engine.loadTexture("assets/environment/grass.png");

    engine.setCurrentCamera(&camera);
    engine.setTargetFPS(60);
    while (!engine.windowShouldClose()) {
        engine.limitFrameRate();

        // Update logic
        float dt = engine.getDeltaTime();

        glm::vec2 moveDir{0.0f, 0.0f};
        constexpr std::array<std::pair<SDL_Scancode, glm::vec2>, 4> keyDirections = {{
            {SDL_SCANCODE_W, {0.0f, -1.0f}},
            {SDL_SCANCODE_S, {0.0f, 1.0f}},
            {SDL_SCANCODE_A, {-1.0f, 0.0f}},
            {SDL_SCANCODE_D, {1.0f, 0.0f}}
        }};
        for (const auto& [key, dir] : keyDirections) {
            if (engine.isKeyPressed(key)) {
                moveDir += dir;
            }
        }
        if (moveDir != glm::vec2{0.0f, 0.0f}) {
            camera.move(glm::normalize(moveDir) * 10.0f);
        }

        // Clear background for render
        engine.clearBackground(100, 149, 237);

        // Render objects Here
        // TODO: ADD OBJECTS TO RENDER
        constexpr SDL_Rect rect = {0, 0, 200, 200};
        constexpr SDL_Rect rect2 = {400, 400, 200, 200};
        engine.drawTextureRect(rect, grassId);
        engine.drawTextureRect(rect2, grassId);

        // Present Render
        engine.presentRender();

        engine.capFrameRate();
    }

    return 0;
}
