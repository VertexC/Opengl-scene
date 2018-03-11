#include <string.h>
#include <iostream>
#include "scene.h"

// window size
GLint windowWidth = 512;
GLint windowHeight = 512;
float speed = 500;

// Build and compile our shader program
Shader *lampShader;
Shader *lightingShader;

// Init the camera object
Camera camera(glm::vec3(0.0f, 0.0f, 3.0f));

// Light attributes
glm::vec3 lightPos(1.2f, 1.0f, 2.0f);

// Set up vertex data (and buffer(s)) and attribute pointers
GLuint VBO, containerVAO, lightVAO;
GLfloat vertices[] = {
    -0.5f, -0.5f, -0.5f, 0.0f, 0.0f, -1.0f,
    0.5f, -0.5f, -0.5f, 0.0f, 0.0f, -1.0f,
    0.5f, 0.5f, -0.5f, 0.0f, 0.0f, -1.0f,
    0.5f, 0.5f, -0.5f, 0.0f, 0.0f, -1.0f,
    -0.5f, 0.5f, -0.5f, 0.0f, 0.0f, -1.0f,
    -0.5f, -0.5f, -0.5f, 0.0f, 0.0f, -1.0f,

    -0.5f, -0.5f, 0.5f, 0.0f, 0.0f, 1.0f,
    0.5f, -0.5f, 0.5f, 0.0f, 0.0f, 1.0f,
    0.5f, 0.5f, 0.5f, 0.0f, 0.0f, 1.0f,
    0.5f, 0.5f, 0.5f, 0.0f, 0.0f, 1.0f,
    -0.5f, 0.5f, 0.5f, 0.0f, 0.0f, 1.0f,
    -0.5f, -0.5f, 0.5f, 0.0f, 0.0f, 1.0f,

    -0.5f, 0.5f, 0.5f, -1.0f, 0.0f, 0.0f,
    -0.5f, 0.5f, -0.5f, -1.0f, 0.0f, 0.0f,
    -0.5f, -0.5f, -0.5f, -1.0f, 0.0f, 0.0f,
    -0.5f, -0.5f, -0.5f, -1.0f, 0.0f, 0.0f,
    -0.5f, -0.5f, 0.5f, -1.0f, 0.0f, 0.0f,
    -0.5f, 0.5f, 0.5f, -1.0f, 0.0f, 0.0f,

    0.5f, 0.5f, 0.5f, 1.0f, 0.0f, 0.0f,
    0.5f, 0.5f, -0.5f, 1.0f, 0.0f, 0.0f,
    0.5f, -0.5f, -0.5f, 1.0f, 0.0f, 0.0f,
    0.5f, -0.5f, -0.5f, 1.0f, 0.0f, 0.0f,
    0.5f, -0.5f, 0.5f, 1.0f, 0.0f, 0.0f,
    0.5f, 0.5f, 0.5f, 1.0f, 0.0f, 0.0f,

    -0.5f, -0.5f, -0.5f, 0.0f, -1.0f, 0.0f,
    0.5f, -0.5f, -0.5f, 0.0f, -1.0f, 0.0f,
    0.5f, -0.5f, 0.5f, 0.0f, -1.0f, 0.0f,
    0.5f, -0.5f, 0.5f, 0.0f, -1.0f, 0.0f,
    -0.5f, -0.5f, 0.5f, 0.0f, -1.0f, 0.0f,
    -0.5f, -0.5f, -0.5f, 0.0f, -1.0f, 0.0f,

    -0.5f, 0.5f, -0.5f, 0.0f, 1.0f, 0.0f,
    0.5f, 0.5f, -0.5f, 0.0f, 1.0f, 0.0f,
    0.5f, 0.5f, 0.5f, 0.0f, 1.0f, 0.0f,
    0.5f, 0.5f, 0.5f, 0.0f, 1.0f, 0.0f,
    -0.5f, 0.5f, 0.5f, 0.0f, 1.0f, 0.0f,
    -0.5f, 0.5f, -0.5f, 0.0f, 1.0f, 0.0f};

void display(void)
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    // Use cooresponding shader when setting uniforms/drawing objects
    lightingShader->Use();
    GLint objectColorLoc = glGetUniformLocation(lightingShader->Program, "objectColor");
    GLint lightColorLoc = glGetUniformLocation(lightingShader->Program, "lightColor");
    GLint lightPosLoc = glGetUniformLocation(lightingShader->Program, "lightPos");
    GLint viewPosLoc = glGetUniformLocation(lightingShader->Program, "viewPos");
    glUniform3f(objectColorLoc, 1.0f, 0.5f, 0.31f);
    glUniform3f(lightColorLoc, 1.0f, 1.0f, 1.0f);
    glUniform3f(lightPosLoc, lightPos.x, lightPos.y, lightPos.z);
    glUniform3f(viewPosLoc, camera.position.x, camera.position.y, camera.position.z);

    // Create camera transformations
    glm::mat4 view;
    view = camera.getViewMatrix();
    glm::mat4 projection = glm::perspective(camera.zoom, (GLfloat)windowWidth / (GLfloat)windowHeight, 0.1f, 100.0f);
    // Get the uniform locations
    GLint modelLoc = glGetUniformLocation(lightingShader->Program, "model");
    GLint viewLoc = glGetUniformLocation(lightingShader->Program, "view");
    GLint projLoc = glGetUniformLocation(lightingShader->Program, "projection");
    // Pass the matrices to the shader
    glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
    glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(projection));

    // Draw the container (using container's vertex attributes)
    glBindVertexArray(containerVAO);
    glm::mat4 model;
    glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
    glDrawArrays(GL_TRIANGLES, 0, 36);
    glBindVertexArray(0);

    // Also draw the lamp object, again binding the appropriate shader
    lampShader->Use();
    // Get location objects for the matrices on the lamp shader (these could be different on a different shader)
    modelLoc = glGetUniformLocation(lampShader->Program, "model");
    viewLoc = glGetUniformLocation(lampShader->Program, "view");
    projLoc = glGetUniformLocation(lampShader->Program, "projection");
    // Set matrices
    glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
    glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(projection));
    model = glm::mat4();
    model = glm::translate(model, lightPos);
    model = glm::scale(model, glm::vec3(0.2f)); // Make it a smaller cube
    glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
    // Draw the light object (using light's vertex attributes)
    glBindVertexArray(lightVAO);
    glDrawArrays(GL_TRIANGLES, 0, 36);
    glBindVertexArray(0);
    glutSwapBuffers();
}

void init(void)
{
    // First, set the container's VAO (and VBO)
    glGenVertexArrays(1, &containerVAO);
    glGenBuffers(1, &VBO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glBindVertexArray(containerVAO);
    // Position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid *)0);
    glEnableVertexAttribArray(0);
    // Normal attribute
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid *)(3 * sizeof(GLfloat)));
    glEnableVertexAttribArray(1);
    glBindVertexArray(0);

    glGenVertexArrays(1, &lightVAO);
    glBindVertexArray(lightVAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    // Set the vertex attributes (only position data for the lamp))
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid *)0); //skip over the normal vectors
    glEnableVertexAttribArray(0);
    glBindVertexArray(0);

    glEnable(GL_DEPTH_TEST);
    glClearColor(0.0, 0.0, 0.0, 1.0);
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
    init();

    lightingShader = new Shader("./shader/lighting.vs", "./shader/lighting.frag");
    lampShader = new Shader("./shader/lamp.vs", "./shader/lamp.frag");

    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutKeyboardFunc(keyboard);
    glutSpecialFunc(specialkey);
    glutTimerFunc(speed, autoRotation, 0);
    glutMouseFunc(mouse);
    glutMainLoop();

    delete lightingShader;
    // delete lampShader;
    return 0;
}
