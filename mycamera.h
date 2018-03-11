#ifndef _MYCAMERA_H__
#define _MYCAMERA_H__

// Std. Includes
#include <vector>

// GL Includes
#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

// camera movement
enum CameraMovement
{
    FORWARD,
    BACKWARD,
    LEFT,
    RIGHT
};

// default parameter
const GLfloat YAW = -90.0f;
const GLfloat PITCH = 0.0f;
const GLfloat ZOOM = 45.0f;
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
    GLfloat zoom;

    Camera(glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3 cameraUp = glm::vec3(0.0f, 1.0f, 0.0f), GLfloat yaw = YAW, GLfloat pitch = PITCH) 
        : front(glm::vec3(0.0f, 0.0f, -1.0f)), zoom(ZOOM)
    {
        this->position = position;
        this->cameraUp = cameraUp;
        this->yaw = yaw;
        this->pitch = pitch;
        this->updateCameraVectors();
    }

    glm::mat4 GetViewMatrix()
    {
        return glm::lookAt(this->position, this->position + this->front, this->up);
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