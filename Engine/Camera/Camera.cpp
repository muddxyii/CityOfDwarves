//
// Created by muddxyii on 8/18/24.
//

#include "Camera.h"

Camera::Camera() = default;

Camera::~Camera() = default;

void Camera::move(glm::vec2 distanceToMove) {

    this->position += distanceToMove;
}

glm::vec2 Camera::getPosition() const {
    return this->position;
}
