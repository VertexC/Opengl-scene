#ifndef _SKYBOX_H__
#define _SKYBOX_H__

#include "scene.h"
#include <vector>
#include <iostream>
class Skybox
{
  public:
    Skybox()
    {
        this->loadFaces();
        glGenTextures(1, &this->textureID);
        glBindTexture(GL_TEXTURE_CUBE_MAP, this->textureID);

        int width, height, channels;
        unsigned char *image;
        std::cout << "here" << std::endl;
        for (GLuint i = 0; i < this->texturesFaces.size(); i++)
        {
            // image = SOIL_load_image(this->texturesFaces[i], &width, &height, &channels, SOIL_LOAD_L);
            image = SOIL_load_image(this->texturesFaces[i], &width, &height, &channels, SOIL_LOAD_RGB);
            std::cout << channels << std::endl;
            glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i,
                         0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
            SOIL_free_image_data(image);
        }

        std::cout << "here1" << std::endl;

        glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
        glBindTexture(GL_TEXTURE_CUBE_MAP, 0);
    }

    void setup()
    {
        float vertices[] = {
            // positions
            -1.0f, 1.0f, -1.0f,
            -1.0f, -1.0f, -1.0f,
            1.0f, -1.0f, -1.0f,
            1.0f, -1.0f, -1.0f,
            1.0f, 1.0f, -1.0f,
            -1.0f, 1.0f, -1.0f,

            -1.0f, -1.0f, 1.0f,
            -1.0f, -1.0f, -1.0f,
            -1.0f, 1.0f, -1.0f,
            -1.0f, 1.0f, -1.0f,
            -1.0f, 1.0f, 1.0f,
            -1.0f, -1.0f, 1.0f,

            1.0f, -1.0f, -1.0f,
            1.0f, -1.0f, 1.0f,
            1.0f, 1.0f, 1.0f,
            1.0f, 1.0f, 1.0f,
            1.0f, 1.0f, -1.0f,
            1.0f, -1.0f, -1.0f,

            -1.0f, -1.0f, 1.0f,
            -1.0f, 1.0f, 1.0f,
            1.0f, 1.0f, 1.0f,
            1.0f, 1.0f, 1.0f,
            1.0f, -1.0f, 1.0f,
            -1.0f, -1.0f, 1.0f,

            -1.0f, 1.0f, -1.0f,
            1.0f, 1.0f, -1.0f,
            1.0f, 1.0f, 1.0f,
            1.0f, 1.0f, 1.0f,
            -1.0f, 1.0f, 1.0f,
            -1.0f, 1.0f, -1.0f,

            -1.0f, -1.0f, -1.0f,
            -1.0f, -1.0f, 1.0f,
            1.0f, -1.0f, -1.0f,
            1.0f, -1.0f, -1.0f,
            -1.0f, -1.0f, 1.0f,
            1.0f, -1.0f, 1.0f};
            
        glGenVertexArrays(1, &this->VAO);
        glGenBuffers(1, &this->VBO);
        glBindVertexArray(this->VAO);
        glBindBuffer(GL_ARRAY_BUFFER, this->VBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), &vertices, GL_STATIC_DRAW);
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid *)0);
        glBindVertexArray(0);
    }

    void loadFaces()
    {
        // this->texturesFaces.push_back("./asset/skybox/skycube_tga/skyrender0001.tga");
        // this->texturesFaces.push_back("./asset/skybox/skycube_tga/skyrender0002.tga");
        // this->texturesFaces.push_back("./asset/skybox/skycube_tga/skyrender0003.tga");
        // this->texturesFaces.push_back("./asset/skybox/skycube_tga/skyrender0004.tga");
        // this->texturesFaces.push_back("./asset/skybox/skycube_tga/skyrender0005.tga");
        // this->texturesFaces.push_back("./asset/skybox/skycube_tga/skyrender0006.tga");

        // this->texturesFaces.push_back("./asset/skybox2/right.jpg");
        // this->texturesFaces.push_back("./asset/skybox2/left.jpg");
        // this->texturesFaces.push_back("./asset/skybox2/top.jpg");
        // this->texturesFaces.push_back("./asset/skybox2/bottom.jpg");
        // this->texturesFaces.push_back("./asset/skybox2/back.jpg");
        // this->texturesFaces.push_back("./asset/skybox2/front.jpg");

        this->texturesFaces.push_back("./asset/hell/nec_hell/hell_ft.tga");
        this->texturesFaces.push_back("./asset/hell/nec_hell/hell_bk.tga");
        this->texturesFaces.push_back("./asset/hell/nec_hell/hell_up.tga");
        this->texturesFaces.push_back("./asset/hell/nec_hell/hell_dn.tga");
        this->texturesFaces.push_back("./asset/hell/nec_hell/hell_rt.tga");
        this->texturesFaces.push_back("./asset/hell/nec_hell/hell_lf.tga");

        // this->texturesFaces.push_back("./asset/moonblood/mp_blood/blood_ft.tga");
        // this->texturesFaces.push_back("./asset/moonblood/mp_blood/blood_bk.tga");
        // this->texturesFaces.push_back("./asset/moonblood/mp_blood/blood_up.tga");
        // this->texturesFaces.push_back("./asset/moonblood/mp_blood/blood_dn.tga");
        // this->texturesFaces.push_back("./asset/moonblood/mp_blood/blood_rt.tga");
        // this->texturesFaces.push_back("./asset/moonblood/mp_blood/blood_lf.tga");
    }

    void Draw(Shader shader)
    {
        shader.Use();
        glBindVertexArray(this->VAO);
        glActiveTexture(GL_TEXTURE0);
        glUniform1i(glGetUniformLocation(shader.Program, "skybox"), 0);
        glBindTexture(GL_TEXTURE_CUBE_MAP, this->textureID);
        glDrawArrays(GL_TRIANGLES, 0, 36);
        glBindVertexArray(0);
    }

    GLuint getTexture(){
        return this->textureID;
    }

  private:
    vector<const GLchar *> texturesFaces;
    GLuint textureID;
    GLuint VAO, VBO;
};

#endif