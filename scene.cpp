#include <string.h>
#include <iostream>
#include "scene.h"
#include "model.h"
#include "skybox.h"
#include "cube.h"
// window size
GLint windowWidth = 512;
GLint windowHeight = 512;
float speed = 2000;

// shader program
Shader *cubeShader;
Shader *skyboxShader;

// model
Skybox *skybox;
Cube *cube;
// Init the camera object
Camera camera(glm::vec3(-10.0f, 0.0f, 0.0f));

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

    cubeShader->Use();
    GLint viewPosLoc = glGetUniformLocation(cubeShader->Program, "viewPos");
    glUniform3f(viewPosLoc, camera.position.x, camera.position.y, camera.position.z);
    glUniform3f(glGetUniformLocation(cubeShader->Program, "cameraPos"), camera.position.x, camera.position.y, camera.position.z);
    // Create camera transformations
    glm::mat4 view = camera.getViewMatrix();
    glm::mat4 projection = glm::perspective(camera.zoom, (GLfloat)windowWidth / (GLfloat)windowHeight, 0.1f, 100.0f);
    glUniformMatrix4fv(glGetUniformLocation(cubeShader->Program, "view"), 1, GL_FALSE, glm::value_ptr(view));
    glUniformMatrix4fv(glGetUniformLocation(cubeShader->Program, "projection"), 1, GL_FALSE, glm::value_ptr(projection));
    cube->Draw(skybox);
    glutSwapBuffers();
}

void init(void)
{

    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);

    skybox->setup();

    cube->setup();

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
    glutTimerFunc(speed, autoRotation, 0);
    std::cout << camera.position.x << " "
              << camera.position.y << " "
              << camera.position.z << std::endl;
    std::cout << camera.pitch << std::endl;
    std::cout << camera.yaw << std::endl;
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

    cubeShader = new Shader("./shader/cube.vs", "./shader/cube.frag");
    skyboxShader = new Shader("./shader/skybox.vs", "./shader/skybox.frag");

    skybox = new Skybox();
    cube = new Cube(cubeShader);

    init();

    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutKeyboardFunc(keyboard);
    glutSpecialFunc(specialkey);
    glutTimerFunc(speed, autoRotation, 0);
    glutMouseFunc(mouse);
    glutMainLoop();

    delete cubeShader;
    delete skyboxShader;
    return 0;
}
