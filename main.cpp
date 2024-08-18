#include <iostream>
#include <SDL2/SDL.h>
#include <glm/glm.hpp>
#include "Engine/Engine.h"

int main()
{
    Engine engine = Engine("OverheadBuilder" ,800, 600);

    engine.setTargetFPS(60);
    while (!engine.windowShouldClose()) {
        engine.limitFrameRate();

        // Update logic
        float dt = engine.getDeltaTime();

        // Clear background for render
        engine.clearBackground(100, 149, 237);

        // Render objects Here
        // TODO: ADD OBJECTS TO RENDER

        // Present Render
        engine.presentRender();

        engine.capFrameRate();
    }

    return 0;
}
