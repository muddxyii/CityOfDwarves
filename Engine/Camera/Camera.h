//
// Created by muddxyii on 8/18/24.
//

#ifndef CAMERA_H
#define CAMERA_H

#include <optional>
#include <SDL2/SDL.h>
#include <glm/glm.hpp>

constexpr Uint32 SCREEN_WIDTH = 800;
constexpr Uint32 SCREEN_HEIGHT = 600;

class Camera {
public:
    Camera();
    ~Camera();

    void move(glm::vec2 distanceToMove);
    [[nodiscard]] glm::vec2 getPosition() const;
    void setLockBox(const SDL_Rect& box);
private:
    glm::vec2 position = {};
    glm::vec2 targetPosition = {};
    std::optional<SDL_Rect> lockBox;
};



#endif //CAMERA_H
