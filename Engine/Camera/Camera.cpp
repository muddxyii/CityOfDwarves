//
// Created by muddxyii on 8/18/24.
//

#include "Camera.h"

#include <algorithm>

Camera::Camera() = default;

Camera::~Camera() = default;

void Camera::move(glm::vec2 distanceToMove) {

    glm::vec2 newPosition = position + distanceToMove;

    if (lockBox) {
        // Constrain x-axis movement
        newPosition.x = std::max(static_cast<float>(lockBox->x),
                        std::min(newPosition.x,
                                 static_cast<float>(lockBox->x + lockBox->w - SCREEN_WIDTH)));

        // Constrain y-axis movement
        newPosition.y = std::max(static_cast<float>(lockBox->y),
                        std::min(newPosition.y,
                                 static_cast<float>(lockBox->y + lockBox->h - SCREEN_HEIGHT)));
    }

    position = newPosition;
}

glm::vec2 Camera::getPosition() const {
    return this->position;
}

void Camera::setLockBox(const SDL_Rect &box) {
    lockBox = box;
}
