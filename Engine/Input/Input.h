//
// Created by muddxyii on 8/17/24.
//

#ifndef INPUT_H
#define INPUT_H

#include <SDL2/SDL.h>

class Input {
public:
    Input();
    ~Input();
    bool pollEvents();
    [[nodiscard]] bool getKeyStatus(SDL_Scancode key) const;
private:
    bool keyStates[SDL_NUM_SCANCODES] = {false};
    bool hasRequestedExit = false;
    void updateKeyStates(const SDL_Event &event);
};



#endif //INPUT_H
