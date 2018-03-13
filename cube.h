#ifndef _CUBE_H__
#define _CUBE_H__

#include "scene.h"
#include "shader.h"
#include "skybox.h"

enum Scale
{
    LARGE = 0,
    SMALL
};

class Cube
{
  public:
    Cube(Shader *shader)
    {
        this->shader = shader;
        this->cubeCenter = glm::vec3(0.0f, 0.0f, 0.0f);
        this->movestep = 2.0f;
        this->scalestep = glm::vec3(1.0f, 1.0f, 1.0f);
        this->cubeScale = glm::vec3(1.0f, 1.0f, 1.0f);
    }

    void Draw(Skybox *skybox)
    {
        // Positions all containers
        glm::vec3 cubePositions[] = {
            glm::vec3(0.0f, 0.0f, 0.0f),
            glm::vec3(2.0f, 5.0f, -15.0f),
            glm::vec3(-1.5f, -2.2f, -2.5f),
            glm::vec3(-3.8f, -2.0f, -12.3f),
            glm::vec3(2.4f, -0.4f, -3.5f),
            glm::vec3(-1.7f, 3.0f, -7.5f),
            glm::vec3(1.3f, -2.0f, -2.5f),
            glm::vec3(1.5f, 2.0f, -2.5f),
            glm::vec3(1.5f, 0.2f, -1.5f),
            glm::vec3(-1.3f, 1.0f, -1.5f)};

        // Light attributes
        glm::vec3 lightPos(0.0f, 1.0f, 2.0f);

        // Use cooresponding shader when setting uniforms/drawing objects
        this->shader->Use();
        // Get the uniform locations
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, this->cubeTexture);
        glActiveTexture(GL_TEXTURE1);
        glBindTexture(GL_TEXTURE_2D, this->cubeSpecularTexture);

        glUniform1i(glGetUniformLocation(this->shader->Program, "skybox"), 2);
        glActiveTexture(GL_TEXTURE2);
        glBindTexture(GL_TEXTURE_CUBE_MAP, skybox->getTexture());

        GLint modelLoc = glGetUniformLocation(this->shader->Program, "model");
        glm::mat4 cubeModel;
        glBindVertexArray(this->VAO);
        for (GLuint i = 0; i < 10; i++)
        {
            cubeModel = glm::mat4();
            cubeModel = glm::scale(cubeModel, this->cubeScale);
            cubeModel = glm::translate(cubeModel, cubePositions[i] + this->cubeCenter);
            // cubeModel = glm::translate(cubeModel, glm::vec3(0.0f, -3.0f, 0.0f));
            GLfloat angle = 20.0f * i;
            cubeModel = glm::rotate(cubeModel, angle, glm::vec3(1.0f, 0.3f, 0.5f));
            glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(cubeModel));
            glDrawArrays(GL_TRIANGLES, 0, 36);
        }
        glBindVertexArray(0);
    }

    void setup()
    {
        GLfloat vertices[] = {
            // Positions          // Normals           // Texture Coords
            -0.5f, -0.5f, -0.5f, 0.0f, 0.0f, -1.0f, 0.0f, 0.0f,
            0.5f, -0.5f, -0.5f, 0.0f, 0.0f, -1.0f, 1.0f, 0.0f,
            0.5f, 0.5f, -0.5f, 0.0f, 0.0f, -1.0f, 1.0f, 1.0f,
            0.5f, 0.5f, -0.5f, 0.0f, 0.0f, -1.0f, 1.0f, 1.0f,
            -0.5f, 0.5f, -0.5f, 0.0f, 0.0f, -1.0f, 0.0f, 1.0f,
            -0.5f, -0.5f, -0.5f, 0.0f, 0.0f, -1.0f, 0.0f, 0.0f,

            -0.5f, -0.5f, 0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f,
            0.5f, -0.5f, 0.5f, 0.0f, 0.0f, 1.0f, 1.0f, 0.0f,
            0.5f, 0.5f, 0.5f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f,
            0.5f, 0.5f, 0.5f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f,
            -0.5f, 0.5f, 0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f,
            -0.5f, -0.5f, 0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f,

            -0.5f, 0.5f, 0.5f, -1.0f, 0.0f, 0.0f, 1.0f, 0.0f,
            -0.5f, 0.5f, -0.5f, -1.0f, 0.0f, 0.0f, 1.0f, 1.0f,
            -0.5f, -0.5f, -0.5f, -1.0f, 0.0f, 0.0f, 0.0f, 1.0f,
            -0.5f, -0.5f, -0.5f, -1.0f, 0.0f, 0.0f, 0.0f, 1.0f,
            -0.5f, -0.5f, 0.5f, -1.0f, 0.0f, 0.0f, 0.0f, 0.0f,
            -0.5f, 0.5f, 0.5f, -1.0f, 0.0f, 0.0f, 1.0f, 0.0f,

            0.5f, 0.5f, 0.5f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f,
            0.5f, 0.5f, -0.5f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f,
            0.5f, -0.5f, -0.5f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f,
            0.5f, -0.5f, -0.5f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f,
            0.5f, -0.5f, 0.5f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f,
            0.5f, 0.5f, 0.5f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f,

            -0.5f, -0.5f, -0.5f, 0.0f, -1.0f, 0.0f, 0.0f, 1.0f,
            0.5f, -0.5f, -0.5f, 0.0f, -1.0f, 0.0f, 1.0f, 1.0f,
            0.5f, -0.5f, 0.5f, 0.0f, -1.0f, 0.0f, 1.0f, 0.0f,
            0.5f, -0.5f, 0.5f, 0.0f, -1.0f, 0.0f, 1.0f, 0.0f,
            -0.5f, -0.5f, 0.5f, 0.0f, -1.0f, 0.0f, 0.0f, 0.0f,
            -0.5f, -0.5f, -0.5f, 0.0f, -1.0f, 0.0f, 0.0f, 1.0f,

            -0.5f, 0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f,
            0.5f, 0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 1.0f, 1.0f,
            0.5f, 0.5f, 0.5f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f,
            0.5f, 0.5f, 0.5f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f,
            -0.5f, 0.5f, 0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f,
            -0.5f, 0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f};

        // First, set the container's VAO (and VBO)
        glGenVertexArrays(1, &this->VAO);
        glGenBuffers(1, &this->VBO);

        glBindBuffer(GL_ARRAY_BUFFER, this->VBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

        glBindVertexArray(this->VAO);
        // Position attribute
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid *)0);
        glEnableVertexAttribArray(0);
        // Normal attribute
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid *)(3 * sizeof(GLfloat)));
        glEnableVertexAttribArray(1);
        glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid *)(6 * sizeof(GLfloat)));
        glEnableVertexAttribArray(2);
        glBindVertexArray(0);

        this->initTexture();
        this->setMetrial();
    }

    void setMetrial()
    {
        this->shader->Use();
        // Positions of the point lights
        glm::vec3 pointLightPositions[] = {
            glm::vec3(0.7f, 0.2f, 2.0f),
            glm::vec3(2.3f, -3.3f, -4.0f),
            glm::vec3(-4.0f, 2.0f, -12.0f),
            glm::vec3(0.0f, 0.0f, -3.0f)};

        // Set material properties
        glUniform1f(glGetUniformLocation(this->shader->Program, "material.shininess"), 16.0f);

        glUniform3f(glGetUniformLocation(this->shader->Program, "dirLight.direction"), -0.2f, -1.0f, -0.3f);
        glUniform3f(glGetUniformLocation(this->shader->Program, "dirLight.ambient"), 0.05f, 0.05f, 0.05f);
        glUniform3f(glGetUniformLocation(this->shader->Program, "dirLight.diffuse"), 0.4f, 0.4f, 0.4f);
        glUniform3f(glGetUniformLocation(this->shader->Program, "dirLight.specular"), 0.5f, 0.5f, 0.5f);

        glUniform3f(glGetUniformLocation(this->shader->Program, "pointLights[0].position"), pointLightPositions[0].x, pointLightPositions[0].y, pointLightPositions[0].z);
        glUniform3f(glGetUniformLocation(this->shader->Program, "pointLights[0].ambient"), 0.05f, 0.05f, 0.05f);
        glUniform3f(glGetUniformLocation(this->shader->Program, "pointLights[0].diffuse"), 0.8f, 0.8f, 0.8f);
        glUniform3f(glGetUniformLocation(this->shader->Program, "pointLights[0].specular"), 1.0f, 1.0f, 1.0f);
        glUniform1f(glGetUniformLocation(this->shader->Program, "pointLights[0].constant"), 1.0f);
        glUniform1f(glGetUniformLocation(this->shader->Program, "pointLights[0].linear"), 0.09);
        glUniform1f(glGetUniformLocation(this->shader->Program, "pointLights[0].quadratic"), 0.032);

        glUniform3f(glGetUniformLocation(this->shader->Program, "pointLights[1].position"), pointLightPositions[1].x, pointLightPositions[1].y, pointLightPositions[1].z);
        glUniform3f(glGetUniformLocation(this->shader->Program, "pointLights[1].ambient"), 0.05f, 0.05f, 0.05f);
        glUniform3f(glGetUniformLocation(this->shader->Program, "pointLights[1].diffuse"), 0.8f, 0.8f, 0.8f);
        glUniform3f(glGetUniformLocation(this->shader->Program, "pointLights[1].specular"), 1.0f, 1.0f, 1.0f);
        glUniform1f(glGetUniformLocation(this->shader->Program, "pointLights[1].constant"), 1.0f);
        glUniform1f(glGetUniformLocation(this->shader->Program, "pointLights[1].linear"), 0.09);
        glUniform1f(glGetUniformLocation(this->shader->Program, "pointLights[1].quadratic"), 0.032);

        glUniform3f(glGetUniformLocation(this->shader->Program, "pointLights[2].position"), pointLightPositions[2].x, pointLightPositions[2].y, pointLightPositions[2].z);
        glUniform3f(glGetUniformLocation(this->shader->Program, "pointLights[2].ambient"), 0.05f, 0.05f, 0.05f);
        glUniform3f(glGetUniformLocation(this->shader->Program, "pointLights[2].diffuse"), 0.8f, 0.8f, 0.8f);
        glUniform3f(glGetUniformLocation(this->shader->Program, "pointLights[2].specular"), 1.0f, 1.0f, 1.0f);
        glUniform1f(glGetUniformLocation(this->shader->Program, "pointLights[2].constant"), 1.0f);
        glUniform1f(glGetUniformLocation(this->shader->Program, "pointLights[2].linear"), 0.09);
        glUniform1f(glGetUniformLocation(this->shader->Program, "pointLights[2].quadratic"), 0.032);

        glUniform3f(glGetUniformLocation(this->shader->Program, "pointLights[3].position"), pointLightPositions[3].x, pointLightPositions[3].y, pointLightPositions[3].z);
        glUniform3f(glGetUniformLocation(this->shader->Program, "pointLights[3].ambient"), 0.05f, 0.05f, 0.05f);
        glUniform3f(glGetUniformLocation(this->shader->Program, "pointLights[3].diffuse"), 0.8f, 0.8f, 0.8f);
        glUniform3f(glGetUniformLocation(this->shader->Program, "pointLights[3].specular"), 1.0f, 1.0f, 1.0f);
        glUniform1f(glGetUniformLocation(this->shader->Program, "pointLights[3].constant"), 1.0f);
        glUniform1f(glGetUniformLocation(this->shader->Program, "pointLights[3].linear"), 0.09);
        glUniform1f(glGetUniformLocation(this->shader->Program, "pointLights[3].quadratic"), 0.032);
    }

    void initTexture()
    {
        int width, height;
        unsigned char *img;

        glGenTextures(1, &this->cubeTexture);
        img = SOIL_load_image("./asset/container.png", &width, &height, 0, SOIL_LOAD_RGB);
        glBindTexture(GL_TEXTURE_2D, this->cubeTexture);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, img);
        glGenerateMipmap(GL_TEXTURE_2D);
        SOIL_free_image_data(img);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST_MIPMAP_NEAREST);
        glBindTexture(GL_TEXTURE_2D, 0);
        this->shader->Use();
        glUniform1i(glGetUniformLocation(this->shader->Program, "material.diffuse"), 0);

        glGenTextures(1, &this->cubeSpecularTexture);
        img = SOIL_load_image("./asset/container_specular_color.png", &width, &height, 0, SOIL_LOAD_RGB);
        glBindTexture(GL_TEXTURE_2D, this->cubeSpecularTexture);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, img);
        glGenerateMipmap(GL_TEXTURE_2D);
        SOIL_free_image_data(img);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST_MIPMAP_NEAREST);
        glBindTexture(GL_TEXTURE_2D, 0);
        this->shader->Use();
        glUniform1i(glGetUniformLocation(this->shader->Program, "material.specular"), 1);
    }

    void setCubeCenter(glm::vec3 cubeCenter)
    {
        this->cubeCenter = cubeCenter;
    }

    void moveCube(Movement direction)
    {
        if (direction == MOVELEFT)
        {
            cubeCenter.x -= this->movestep;
        }
        else if (direction == MOVERIGHT)
        {
            cubeCenter.x += this->movestep;
        }
        else if (direction == MOVEUP)
        {
            cubeCenter.y += this->movestep;
        }
        else if (direction == MOVEDONE)
        {
            cubeCenter.y -= this->movestep;
        }
        else if (direction == MOVEFRONT)
        {
            cubeCenter.z -= this->movestep;
        }
        else if (direction == MOVEBACK)
        {
            cubeCenter.z += this->movestep;
        }
    }

    void scaleCube(Scale zoom)
    {
        if (zoom == LARGE)
        {
            this->cubeScale += scalestep;
        }
        else if (zoom == SMALL)
        {
            this->cubeScale -= scalestep;
        }
    }

  private:
    GLuint VAO, VBO;
    GLuint cubeTexture, cubeSpecularTexture;
    Shader *shader;
    float movestep;
    glm::vec3 cubeScale;
    glm::vec3 scalestep;
    glm::vec3 cubeCenter;
};

#endif