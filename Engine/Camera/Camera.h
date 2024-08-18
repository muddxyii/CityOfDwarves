//
// Created by muddxyii on 8/18/24.
//

#ifndef CAMERA_H
#define CAMERA_H

#include <glm/glm.hpp>

class Camera {
public:
    Camera();
    ~Camera();

    void move(glm::vec2 distanceToMove);
    glm::vec2 getPosition() const;
private:
    glm::vec2 position = {};
    glm::vec2 targetPosition = {};
};



#endif //CAMERA_H
