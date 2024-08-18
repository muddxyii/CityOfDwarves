//
// Created by muddxyii on 8/17/24.
//

#include "Input.h"

Input::Input() = default;

Input::~Input() = default;

// Returns true if exit request received
// Updates key states
bool Input::pollEvents() {
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        if (event.type == SDL_QUIT) {
            hasRequestedExit = true;
        }
        updateKeyStates(event);
    }
    if (getKeyStatus(SDL_SCANCODE_ESCAPE)) {
        hasRequestedExit = true;
    }

    return hasRequestedExit;
}

bool Input::getKeyStatus(const SDL_Scancode key) const {
    return keyStates[key];
}

void Input::updateKeyStates(const SDL_Event &event) {
    if (event.type == SDL_KEYDOWN) {
        keyStates[event.key.keysym.scancode] = true;
    } else if (event.type == SDL_KEYUP) {
        keyStates[event.key.keysym.scancode] = false;
    }
}
