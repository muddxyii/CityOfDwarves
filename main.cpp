#include <iostream>
#include <SDL2/SDL.h>
#include <glm/glm.hpp>
#include "Engine/Engine.h"

int main()
{
    Engine engine = Engine(800, 600);

    while (!engine.windowShouldClose()) {
        engine.clearBackground();
        engine.presentRender();
    }

    return 0;
}
