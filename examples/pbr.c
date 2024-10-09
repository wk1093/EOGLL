#include "eogll.h"

int main() {
    if (eogllInit() != EOGLL_SUCCESS) {
        return 1;
    }

    EogllWindow* window = eogllCreateWindow(800, 600, "EOGLL: PBR", eogllDefaultWindowHints());

    eogllEnableDepth();

    EogllShaderProgram* shaderProgram = eogllLinkProgramFromFile("resources/shaders/pbr_vert.glsl", "resources/shaders/pbr_frag.glsl");

    EogllModel model = eogllCreateModel(); // matrix
    eogllRotateModel(&model, 45.0f,  (vec3) {0.0f, 1.0f, 0.0f}); // rotate 45 degrees on y axis

    vec3 lights[2] = {
        {0.0f, 2.0f, 0.0f},
        {1.0f, 2.0f, 0.0f}
    };
    vec3 lightColors[2] = {
        {1.0f, 1.0f, 1.0f},
        {0.5f, 0.5f, 1.0f}
    };

    EogllTexture* albedo =    eogllCreateTexture("resources/textures/rusted_iron/albedo.png");
    EogllTexture* normal =    eogllCreateTexture("resources/textures/rusted_iron/normal.png");
    EogllTexture* metallic =  eogllCreateTexture("resources/textures/rusted_iron/metallic.png");
    EogllTexture* roughness = eogllCreateTexture("resources/textures/rusted_iron/roughness.png");
    EogllTexture* ao =        eogllCreateTexture("resources/textures/rusted_iron/ao.png");

    EogllCamera camera = eogllCreateCamera();

    eogllTranslateCamera3f(&camera, 0.0f, 0.0f, 5.0f);

    EogllProjection projection = eogllPerspectiveProjection(45.0f, 0.01f, 100000.0f);

    // similar to eogllCreateAttribBuilder but it also is used to load the model from a file.
    EogllObjectAttrs objMode = eogllCreateObjectAttrs();
    eogllAddObjectAttr(&objMode, GL_FLOAT, 3, EOGLL_ATTR_POSITION);
    eogllAddObjectAttr(&objMode, GL_FLOAT, 3, EOGLL_ATTR_NORMAL);
    eogllAddObjectAttr(&objMode, GL_FLOAT, 2, EOGLL_ATTR_TEXTURE);
    // time to load the model
    EogllBufferObject bufferObject = eogllLoadBufferObject("resources/models/cube.obj", objMode, GL_STATIC_DRAW);

    double speed = 1.0;
    double lastSpeed = 0.0;

    double moveSpeed = 1.0;
    double sensitivity = 0.1;

    bool mouseDisabled = false;

    while (!eogllWindowShouldClose(window)) {

        eogllRotateModel(&model, 50.0f, (vec3) {5.2f*window->dt*speed, 10.0f*window->dt*speed, 1.23f*window->dt*speed});

        if (window->isDown[GLFW_KEY_LEFT]) {
            speed -= window->dt*5;
        }
        if (window->isDown[GLFW_KEY_RIGHT]) {
            speed += window->dt*5;
        }
        if (window->isDown[GLFW_KEY_UP]) {
            moveSpeed += window->dt*5;
        }
        if (window->isDown[GLFW_KEY_DOWN]) {
            moveSpeed -= window->dt*5;
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
            eogllMoveCamera(&camera, EOGLL_FORWARD, window->dt*moveSpeed);
        }
        if (window->isDown[GLFW_KEY_S]) {
            eogllMoveCamera(&camera, EOGLL_BACKWARD, window->dt*moveSpeed);
        }
        if (window->isDown[GLFW_KEY_A]) {
            eogllMoveCamera(&camera, EOGLL_LEFT, window->dt*moveSpeed);
        }
        if (window->isDown[GLFW_KEY_D]) {
            eogllMoveCamera(&camera, EOGLL_RIGHT, window->dt*moveSpeed);
        }
        if (window->isDown[GLFW_KEY_LEFT_SHIFT]) {
            eogllMoveCamera(&camera, EOGLL_DOWN, window->dt*moveSpeed);
        }
        if (window->isDown[GLFW_KEY_SPACE]) {
            eogllMoveCamera(&camera, EOGLL_UP, window->dt*moveSpeed);
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
        eogllSetUniform3fl(shaderProgram, "lights", lights, 2);
        eogllSetUniform3fl(shaderProgram, "lightColors", lightColors, 2);
        eogllBindTextureUniform(albedo, shaderProgram, "albedo", 0);
        eogllBindTextureUniform(normal, shaderProgram, "normal", 1);
        eogllBindTextureUniform(metallic, shaderProgram, "metallic", 2);
        eogllBindTextureUniform(roughness, shaderProgram, "roughness", 3);
        eogllBindTextureUniform(ao, shaderProgram, "ao", 4);
        eogllSetUniform3f(shaderProgram, "viewPos", camera.pos[0], camera.pos[1], camera.pos[2]);
        eogllDrawBufferObject(&bufferObject, GL_TRIANGLES);

        eogllSwapBuffers(window);
        eogllPollEvents(window);
    }
}