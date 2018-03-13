#include <string.h>
#include <iostream>
#include "scene.h"
#include "model.h"
#include "skybox.h"
// window size
GLint windowWidth = 512;
GLint windowHeight = 512;
float speed = 500;

// shader program
Shader *lampShader;
Shader *lightingShader;
Shader *moonShader;
Shader *skyboxShader;

// model
Model *moon;
Skybox *skybox;
// Init the camera object
Camera camera(glm::vec3(0.0f, 0.0f, 3.0f));

// Light attributes
glm::vec3 lightPos(0.0f, 1.0f, 2.0f);

// Set up vertex data (and buffer(s)) and attribute pointers
GLuint VBO, containerVAO, lightVAO;
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

// Positions all containers
GLfloat angle = 0.0f;
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

// Positions of the point lights
glm::vec3 pointLightPositions[] = {
    glm::vec3(0.7f, 0.2f, 2.0f),
    glm::vec3(2.3f, -3.3f, -4.0f),
    glm::vec3(-4.0f, 2.0f, -12.0f),
    glm::vec3(0.0f, 0.0f, -3.0f)};

// texture
GLuint containerTexture, containerSpecularTexture;

void display(void)
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glDepthMask(GL_FALSE);
    skyboxShader->Use();
    glm::mat4 skyboxProjection = glm::perspective(camera.zoom, (float)windowWidth / (float)windowHeight, 0.1f, 100.0f);
    glm::mat4 skyboxView = glm::mat4(glm::mat3(camera.getViewMatrix()));
    glUniformMatrix4fv(glGetUniformLocation(skyboxShader->Program, "projection"), 1, GL_FALSE, glm::value_ptr(skyboxProjection));
    glUniformMatrix4fv(glGetUniformLocation(skyboxShader->Program, "view"), 1, GL_FALSE, glm::value_ptr(skyboxView));
    // Draw skybox
    skybox->Draw(*skyboxShader);
    glDepthMask(GL_TRUE);
    // glDepthMask(GL_TRUE);
    // // Use cooresponding shader when setting uniforms/drawing objects
    // lightingShader->Use();
    // GLint lightDirLoc = glGetUniformLocation(lightingShader->Program, "light.direction");
    // GLint viewPosLoc = glGetUniformLocation(lightingShader->Program, "viewPos");
    // glUniform3f(lightDirLoc, -0.2f, -1.0f, -0.3f);
    // glUniform3f(viewPosLoc, camera.position.x, camera.position.y, camera.position.z);

    // // Set material properties
    // glUniform1f(glGetUniformLocation(lightingShader->Program, "material.shininess"), 16.0f);

    // // Directional light
    // glUniform3f(glGetUniformLocation(lightingShader->Program, "dirLight.direction"), -0.2f, -1.0f, -0.3f);
    // glUniform3f(glGetUniformLocation(lightingShader->Program, "dirLight.ambient"), 0.05f, 0.05f, 0.05f);
    // glUniform3f(glGetUniformLocation(lightingShader->Program, "dirLight.diffuse"), 0.4f, 0.4f, 0.4f);
    // glUniform3f(glGetUniformLocation(lightingShader->Program, "dirLight.specular"), 0.5f, 0.5f, 0.5f);
    // // Point light
    // glUniform3f(glGetUniformLocation(lightingShader->Program, "pointLights[0].position"), pointLightPositions[0].x, pointLightPositions[0].y, pointLightPositions[0].z);
    // glUniform3f(glGetUniformLocation(lightingShader->Program, "pointLights[0].ambient"), 0.05f, 0.05f, 0.05f);
    // glUniform3f(glGetUniformLocation(lightingShader->Program, "pointLights[0].diffuse"), 0.8f, 0.8f, 0.8f);
    // glUniform3f(glGetUniformLocation(lightingShader->Program, "pointLights[0].specular"), 1.0f, 1.0f, 1.0f);
    // glUniform1f(glGetUniformLocation(lightingShader->Program, "pointLights[0].constant"), 1.0f);
    // glUniform1f(glGetUniformLocation(lightingShader->Program, "pointLights[0].linear"), 0.09);
    // glUniform1f(glGetUniformLocation(lightingShader->Program, "pointLights[0].quadratic"), 0.032);
    // // Point light
    // glUniform3f(glGetUniformLocation(lightingShader->Program, "pointLights[1].position"), pointLightPositions[1].x, pointLightPositions[1].y, pointLightPositions[1].z);
    // glUniform3f(glGetUniformLocation(lightingShader->Program, "pointLights[1].ambient"), 0.05f, 0.05f, 0.05f);
    // glUniform3f(glGetUniformLocation(lightingShader->Program, "pointLights[1].diffuse"), 0.8f, 0.8f, 0.8f);
    // glUniform3f(glGetUniformLocation(lightingShader->Program, "pointLights[1].specular"), 1.0f, 1.0f, 1.0f);
    // glUniform1f(glGetUniformLocation(lightingShader->Program, "pointLights[1].constant"), 1.0f);
    // glUniform1f(glGetUniformLocation(lightingShader->Program, "pointLights[1].linear"), 0.09);
    // glUniform1f(glGetUniformLocation(lightingShader->Program, "pointLights[1].quadratic"), 0.032);
    // // Point light
    // glUniform3f(glGetUniformLocation(lightingShader->Program, "pointLights[2].position"), pointLightPositions[2].x, pointLightPositions[2].y, pointLightPositions[2].z);
    // glUniform3f(glGetUniformLocation(lightingShader->Program, "pointLights[2].ambient"), 0.05f, 0.05f, 0.05f);
    // glUniform3f(glGetUniformLocation(lightingShader->Program, "pointLights[2].diffuse"), 0.8f, 0.8f, 0.8f);
    // glUniform3f(glGetUniformLocation(lightingShader->Program, "pointLights[2].specular"), 1.0f, 1.0f, 1.0f);
    // glUniform1f(glGetUniformLocation(lightingShader->Program, "pointLights[2].constant"), 1.0f);
    // glUniform1f(glGetUniformLocation(lightingShader->Program, "pointLights[2].linear"), 0.09);
    // glUniform1f(glGetUniformLocation(lightingShader->Program, "pointLights[2].quadratic"), 0.032);
    // // Point light 4
    // glUniform3f(glGetUniformLocation(lightingShader->Program, "pointLights[3].position"), pointLightPositions[3].x, pointLightPositions[3].y, pointLightPositions[3].z);
    // glUniform3f(glGetUniformLocation(lightingShader->Program, "pointLights[3].ambient"), 0.05f, 0.05f, 0.05f);
    // glUniform3f(glGetUniformLocation(lightingShader->Program, "pointLights[3].diffuse"), 0.8f, 0.8f, 0.8f);
    // glUniform3f(glGetUniformLocation(lightingShader->Program, "pointLights[3].specular"), 1.0f, 1.0f, 1.0f);
    // glUniform1f(glGetUniformLocation(lightingShader->Program, "pointLights[3].constant"), 1.0f);
    // glUniform1f(glGetUniformLocation(lightingShader->Program, "pointLights[3].linear"), 0.09);
    // glUniform1f(glGetUniformLocation(lightingShader->Program, "pointLights[3].quadratic"), 0.032);
    // // Create camera transformations
    // glm::mat4 view;
    // view = camera.getViewMatrix();
    // glm::mat4 projection = glm::perspective(camera.zoom, (GLfloat)windowWidth / (GLfloat)windowHeight, 0.1f, 100.0f);
    // // Get the uniform locations
    // GLint modelLoc = glGetUniformLocation(lightingShader->Program, "model");
    // GLint viewLoc = glGetUniformLocation(lightingShader->Program, "view");
    // GLint projLoc = glGetUniformLocation(lightingShader->Program, "projection");
    // // Pass the matrices to the shader
    // glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
    // glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(projection));

    // glActiveTexture(GL_TEXTURE0);
    // glBindTexture(GL_TEXTURE_2D, containerTexture);
    // glActiveTexture(GL_TEXTURE1);
    // glBindTexture(GL_TEXTURE_2D, containerSpecularTexture);
    // // // Draw the container (using container's vertex attributes)
    // // glBindVertexArray(containerVAO);
    // // glm::mat4 model;
    // // glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
    // // glDrawArrays(GL_TRIANGLES, 0, 36);
    // // glBindVertexArray(0);

    // glm::mat4 cubeModel;
    // glBindVertexArray(containerVAO);
    // for (GLuint i = 0; i < 10; i++)
    // {
    //     cubeModel = glm::mat4();
    //     cubeModel = glm::translate(cubeModel, cubePositions[i]);
    //     GLfloat angle = 20.0f * i;
    //     cubeModel = glm::rotate(cubeModel, angle, glm::vec3(1.0f, 0.3f, 0.5f));
    //     glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(cubeModel));
    //     glDrawArrays(GL_TRIANGLES, 0, 36);
    // }
    // glBindVertexArray(0);

    // // moonShader->Use(); // <-- Don't forget this one!
    // // // Transformation matrices
    // // glm::mat4 projection = glm::perspective(camera.zoom, (float)windowWidth / (float)windowHeight, 0.1f, 100.0f);
    // // glm::mat4 view = camera.getViewMatrix();
    // // glUniformMatrix4fv(glGetUniformLocation(moonShader->Program, "projection"), 1, GL_FALSE, glm::value_ptr(projection));
    // // glUniformMatrix4fv(glGetUniformLocation(moonShader->Program, "view"), 1, GL_FALSE, glm::value_ptr(view));

    // // // Draw the loaded model
    // // glm::mat4 moonModel;
    // // moonModel = glm::translate(moonModel, glm::vec3(0.0f, 0.0f, 0.0f)); // Translate it down a bit so it's at the center of the scene
    // // moonModel = glm::scale(moonModel, glm::vec3(1.0f, 1.0f, 1.0f));     // It's a bit too big for our scene, so scale it down
    // // glUniformMatrix4fv(glGetUniformLocation(moonShader->Program, "model"), 1, GL_FALSE, glm::value_ptr(moonModel));
    // // moon->Draw(*moonShader);
    // // Draw the loaded model

    glutSwapBuffers();
}

void initTexture()
{
    int width, height;
    unsigned char *img1;

    glGenTextures(1, &containerTexture);
    img1 = SOIL_load_image("./asset/container.png", &width, &height, 0, SOIL_LOAD_RGB);
    glBindTexture(GL_TEXTURE_2D, containerTexture);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, img1);
    glGenerateMipmap(GL_TEXTURE_2D);
    SOIL_free_image_data(img1);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST_MIPMAP_NEAREST);
    glBindTexture(GL_TEXTURE_2D, 0);
    lightingShader->Use();
    glUniform1i(glGetUniformLocation(lightingShader->Program, "material.diffuse"), 0);

    unsigned char *img;
    glGenTextures(1, &containerSpecularTexture);
    img = SOIL_load_image("./asset/container_specular_color.png", &width, &height, 0, SOIL_LOAD_RGB);
    glBindTexture(GL_TEXTURE_2D, containerSpecularTexture);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, img);
    glGenerateMipmap(GL_TEXTURE_2D);
    SOIL_free_image_data(img);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST_MIPMAP_NEAREST);
    glBindTexture(GL_TEXTURE_2D, 0);
    lightingShader->Use();
    glUniform1i(glGetUniformLocation(lightingShader->Program, "material.specular"), 1);
}

void init(void)
{

    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);

    skybox->setup();

    // std::cout << "begin init" << std::endl;
    // initTexture();
    // std::cout << "load in texture" << std::endl;

    // // First, set the container's VAO (and VBO)
    // glGenVertexArrays(1, &containerVAO);
    // glGenBuffers(1, &VBO);

    // glBindBuffer(GL_ARRAY_BUFFER, VBO);
    // glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    // glBindVertexArray(containerVAO);
    // // Position attribute
    // glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid *)0);
    // glEnableVertexAttribArray(0);
    // // Normal attribute
    // glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid *)(3 * sizeof(GLfloat)));
    // glEnableVertexAttribArray(1);
    // glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid *)(6 * sizeof(GLfloat)));
    // glEnableVertexAttribArray(2);
    // glBindVertexArray(0);

    // glGenVertexArrays(1, &lightVAO);
    // glBindVertexArray(lightVAO);
    // glBindBuffer(GL_ARRAY_BUFFER, VBO);
    // // Set the vertex attributes (only position data for the lamp))
    // glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid *)0); //skip over the normal vectors
    // glEnableVertexAttribArray(0);
    // glBindVertexArray(0);

    glClearColor(0.1, 0.1, 0.1, 1.0);
}

void mouse(int button, int state, int x, int y)
{
    glutPostRedisplay();
}

void reshape(int width, int height)
{
    glutReshapeWindow(windowWidth, windowHeight);
}

void keyboard(unsigned char key, int x, int y)
{
    switch (key)
    {
    case 033: // Escape Key
    case 'q':
    case 'Q':
        exit(EXIT_SUCCESS);
        break;
    case 'a':
        camera.turnCamera(TURNLEFT);
        break;
    case 'd':
        camera.turnCamera(TURNRIGHT);
        break;
    case 'w':
        camera.turnCamera(TURNUP);
        break;
    case 's':
        camera.turnCamera(TURNDOWN);
        break;
    }
}

void specialkey(int key, int x, int y)
{
    switch (key)
    {
    case GLUT_KEY_LEFT:
        camera.moveCamera(MOVELEFT);
        break;
    case GLUT_KEY_RIGHT:
        camera.moveCamera(MOVERIGHT);
        break;
    case GLUT_KEY_UP:
        camera.moveCamera(FORWARD);
        break;
    case GLUT_KEY_DOWN:
        camera.moveCamera(BACKWARD);
        break;
    }
}

void autoRotation(int value)
{
    angle += 5.0f;
    if (angle > 360.0f)
    {
        angle -= 360.0f;
    }
    glutTimerFunc(speed, autoRotation, 0);
}

int main(int argc, char **argv)
{
    /*OpenGL*/
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);

    glutInitContextVersion(3, 2);
    glutInitContextProfile(GLUT_CORE_PROFILE);
    glutInitWindowPosition(300, 300);
    glutInitWindowSize(windowWidth, windowHeight);
    glutCreateWindow("scene");
    glewExperimental = GL_TRUE;
    GLenum err = glewInit();
    if (err != GLEW_OK)
        exit(1);
    if (!GLEW_VERSION_2_1)
        exit(1);

    lightingShader = new Shader("./shader/lighting.vs", "./shader/lighting.frag");
    lampShader = new Shader("./shader/lamp.vs", "./shader/lamp.frag");
    moonShader = new Shader("./shader/moon.vs", "./shader/moon.frag");
    skyboxShader = new Shader("./shader/skybox.vs", "./shader/skybox.frag");
    // std::cout << "load model" << std::endl;
    // moon = new Model("./asset/moon/Moon.obj");
    // std::cout << "load complete" << std::endl;
    std::cout << "load in skybox" << endl;
    skybox = new Skybox();
    std::cout << "load in skybox done" << endl;

    init();

    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutKeyboardFunc(keyboard);
    glutSpecialFunc(specialkey);
    glutTimerFunc(speed, autoRotation, 0);
    glutMouseFunc(mouse);
    glutMainLoop();

    delete lightingShader;
    delete lampShader;
    delete moonShader;
    return 0;
}
