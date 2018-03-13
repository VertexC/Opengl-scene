#ifndef _MYCAMERA_H__
#define _MYCAMERA_H__

// Std. Includes
#include <vector>

// GL Includes
#include "scene.h"
// camera movement
enum Movement
{
    MOVELEFT = 0,
    MOVERIGHT,
    MOVEUP,
    MOVEDONE,
    MOVEFRONT,
    MOVEBACK
};

enum CameraTurnAround
{
    TURNUP = 0,
    TURNDOWN,
    TURNLEFT,
    TURNRIGHT
};

// default parameter
const GLfloat YAW = -90.0f;
const GLfloat PITCH = 0.0f;
const GLfloat ZOOM = 45.0f;
const GLfloat MOVEMENTSPEED = 1.0f;
const GLfloat TURNAROUNDSPEED = 5.0f;

class Camera
{
  public:
    glm::vec3 position;
    glm::vec3 front;
    glm::vec3 up; // up vector in LookAt()
    glm::vec3 right;
    glm::vec3 cameraUp; // y vector of camera

    GLfloat yaw;
    GLfloat pitch;

    GLfloat movementSpeed;
    GLfloat turnAroundSpeed;
    GLfloat zoom;

    Camera(glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3 cameraUp = glm::vec3(0.0f, 1.0f, 0.0f), GLfloat yaw = YAW, GLfloat pitch = PITCH)
        : front(glm::vec3(0.0f, 0.0f, -1.0f)), zoom(ZOOM), movementSpeed(MOVEMENTSPEED), turnAroundSpeed(TURNAROUNDSPEED)
    {
        this->position = position;
        this->cameraUp = cameraUp;
        this->yaw = yaw;
        this->pitch = pitch;
        this->updateCameraVectors();
    }

    glm::mat4 getViewMatrix()
    {
        return glm::lookAt(this->position, this->position + this->front, this->up);
    }

    void moveCamera(Movement direction)
    {
        if (direction == MOVEFRONT)
            this->position += this->front * this->movementSpeed;
        if (direction == MOVEBACK)
            this->position -= this->front * this->movementSpeed;
        if (direction == MOVELEFT)
            this->position += this->right * this->movementSpeed;
        if (direction == MOVERIGHT)
            this->position -= this->right * this->movementSpeed;
    }

    void turnCamera(CameraTurnAround direction)
    {
        if (direction == TURNUP)
            this->pitch += this->turnAroundSpeed;
        if (direction == TURNDOWN)
            this->pitch -= this->turnAroundSpeed;
        if (this->pitch > 89.0f)
            this->pitch = 89.0f;
        if (this->pitch < -89.0f)
            this->pitch = -89.0f;

        if (direction == TURNLEFT)
            this->yaw -= this->turnAroundSpeed;
        if (direction == TURNRIGHT)
            this->yaw += this->turnAroundSpeed;
        if (this->yaw < 0.0f)
            this->yaw += 360.0f;
        if (this->yaw > 360.0f)
            this->yaw -= 360.0f;
        this->updateCameraVectors();
    }

  private:
    void updateCameraVectors()
    {
        glm::vec3 front;
        front.x = cos(glm::radians(this->yaw)) * cos(glm::radians(this->pitch));
        front.y = sin(glm::radians(this->pitch));
        front.z = sin(glm::radians(this->yaw) * cos(glm::radians(this->pitch)));
        this->front = glm::normalize(front);
        this->right = glm::normalize(glm::cross(this->front, this->cameraUp));
        this->up = glm::normalize(glm::cross(this->right, this->front));
    }
};

#endif