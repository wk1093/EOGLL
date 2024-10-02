#include "eogll.h"

int main() {
    if (eogllInit() != EOGLL_SUCCESS) {
        return 1;
    }

    EogllWindow* window = eogllCreateWindow(800, 600, "LearnEOGLL", eogllDefaultWindowHints());

    eogllEnableDepth();

    EogllShaderProgram* shaderProgram = eogllLinkProgramFromFile("resources/shaders/tex_vertex.glsl", "resources/shaders/tex_fragment.glsl");

    EogllModel model = eogllCreateModel(); // matrix
    eogllRotateModel(&model, 45.0f,  (vec3) {0.0f, 1.0f, 0.0f}); // rotate 45 degrees on y axis

    EogllTexture* texture = eogllCreateTexture("resources/textures/thing.png");

    EogllCamera camera = eogllCreateCamera();

    eogllTranslateCamera3f(&camera, 0.0f, 0.0f, 5.0f);

    EogllProjection projection = eogllPerspectiveProjection(45.0f, 0.01f, 100000.0f);

    // similar to eogllCreateAttribBuilder but it also is used to load the model from a file.
    EogllObjectAttrs objMode = eogllCreateObjectAttrs();
    eogllAddObjectAttr(&objMode, GL_FLOAT, 3, EOGLL_ATTR_POSITION);
    eogllAddObjectAttr(&objMode, GL_FLOAT, 3, EOGLL_ATTR_NORMAL);
    eogllAddObjectAttr(&objMode, GL_FLOAT, 2, EOGLL_ATTR_TEXTURE);
    // time to load the model
    EogllBufferObject bufferObject = eogllLoadBufferObject("resources/models/untitled.obj", objMode, GL_STATIC_DRAW);

    double lastTime = eogllGetTime();

    double speed = 1.0;
    double lastSpeed = 0.0;

    double moveSpeed = 1.0;
    double sensitivity = 0.1;

    bool mouseDisabled = false;

    while (!eogllWindowShouldClose(window)) {
        double currentTime = eogllGetTime();
        float deltaTime = (float)(currentTime - lastTime);
        lastTime = currentTime;

        eogllRotateModel(&model, 50.0f, (vec3) {5.2f*deltaTime*speed, 10.0f*deltaTime*speed, 1.23f*deltaTime*speed});

        if (window->isDown[GLFW_KEY_LEFT]) {
            speed -= deltaTime*5;
        }
        if (window->isDown[GLFW_KEY_RIGHT]) {
            speed += deltaTime*5;
        }
        if (window->isDown[GLFW_KEY_UP]) {
            moveSpeed += deltaTime*5;
        }
        if (window->isDown[GLFW_KEY_DOWN]) {
            moveSpeed -= deltaTime*5;
        }
        if (window->press[GLFW_KEY_E]) {
            if (lastSpeed == 0.0) {
                lastSpeed = speed;
                speed = 0.0;
            } else {
                speed = lastSpeed;
                lastSpeed = 0.0;
            }
        }

        if (window->isDown[GLFW_KEY_W]) {
            eogllMoveCamera(&camera, EOGLL_FORWARD, deltaTime*moveSpeed);
        }
        if (window->isDown[GLFW_KEY_S]) {
            eogllMoveCamera(&camera, EOGLL_BACKWARD, deltaTime*moveSpeed);
        }
        if (window->isDown[GLFW_KEY_A]) {
            eogllMoveCamera(&camera, EOGLL_LEFT, deltaTime*moveSpeed);
        }
        if (window->isDown[GLFW_KEY_D]) {
            eogllMoveCamera(&camera, EOGLL_RIGHT, deltaTime*moveSpeed);
        }
        if (window->isDown[GLFW_KEY_LEFT_SHIFT]) {
            eogllMoveCamera(&camera, EOGLL_DOWN, deltaTime*moveSpeed);
        }
        if (window->isDown[GLFW_KEY_SPACE]) {
            eogllMoveCamera(&camera, EOGLL_UP, deltaTime*moveSpeed);
        }

        if (window->mouseIsDown[GLFW_MOUSE_BUTTON_LEFT]) {
            if (!mouseDisabled) {
                mouseDisabled = true;
                eogllSetCursorMode(window, EOGLL_CURSOR_DISABLED);
            }
        }
        if (window->isDown[GLFW_KEY_ESCAPE]) {
            if (mouseDisabled) {
                mouseDisabled = false;
                eogllSetCursorMode(window, EOGLL_CURSOR_NORMAL);
            }
        }

        if (mouseDisabled) {
            if (window->mousedx != 0) {
                eogllYawCamera(&camera, window->mousedx * sensitivity);
                window->mousedx = 0;
            }
            if (window->mousedy != 0) {
                eogllPitchCamera(&camera, -window->mousedy * sensitivity);
                window->mousedy = 0;
            }
        }
        


        glClearColor(0.0f, 0.0f, 0.0f, 1.0f); // clear color buffer
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // clear depth buffer

        eogllUseProgram(shaderProgram);
        eogllUpdateCameraMatrix(&camera, shaderProgram, "view");
        eogllUpdateProjectionMatrix(&projection, shaderProgram, "projection", window->width, window->height);
        eogllUpdateModelMatrix(&model, shaderProgram, "model");
        eogllBindTextureUniform(texture, shaderProgram, "tex", 0);
        eogllDrawBufferObject(&bufferObject, GL_TRIANGLES);

        eogllSwapBuffers(window);
        eogllPollEvents(window);
    }
}