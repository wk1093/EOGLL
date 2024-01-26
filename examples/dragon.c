#include "eogll.h"

int main() {
    if (eogllInit() != EOGLL_SUCCESS) {
        return 1;
    }

    EogllWindow* window = eogllCreateWindow(800, 600, "LearnEOGLL", eogllDefaultWindowHints());

    eogllEnableDepth();

    EogllShaderProgram* shaderProgram = eogllLinkProgramFromFile("resources/shaders/vertex.glsl", "resources/shaders/fragment.glsl");

    EogllModel model = eogllCreateModel(); // matrix
    eogllRotateModel(&model, (vec3) {0.0f, 45.0f, 0.0f}); // rotate 45 degrees on y axis

    EogllCamera camera = eogllCreateCamera();

    eogllTranslateCamera3f(&camera, 0.0f, 0.0f, 5.0f);

    EogllProjection projection = eogllPerspectiveProjection(45.0f, 0.1f, 100.0f);

    // similar to eogllCreateAttribBuilder but it also is used to load the model from a file.
    EogllObjectAttrs objMode = eogllCreateObjectAttrs();
    eogllAddObjectAttr(&objMode, GL_FLOAT, 3, EOGLL_ATTR_POSITION);
    eogllAddObjectAttr(&objMode, GL_FLOAT, 3, EOGLL_ATTR_NORMAL);
    // time to load the model
    double start = eogllGetTime();
    EogllBufferObject bufferObject = eogllLoadBufferObject("resources/models/dragon.obj", objMode, GL_STATIC_DRAW);
    double end = eogllGetTime();

    EOGLL_LOG_INFO(stdout, "Loaded model in %f seconds\n", end - start);

    while (!eogllWindowShouldClose(window)) {
        eogllRotateModel(&model, (vec3) {0.52f, 1.0f, 0.123f});

        if (window->isDown[GLFW_KEY_ESCAPE]) {
            eogllSetWindowShouldClose(window, true);
        }
        if (window->press[GLFW_KEY_SPACE]) {
            EOGLL_LOG_INFO(stdout, "Space pressed\n");
            eogllSetWindowSize(window, 800, 600);
        }
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f); // clear color buffer
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // clear depth buffer

        eogllUseProgram(shaderProgram);
        eogllUpdateCameraMatrix(&camera, shaderProgram, "view");
        eogllUpdateProjectionMatrix(&projection, shaderProgram, "projection", window->width, window->height);
        eogllUpdateModelMatrix(&model, shaderProgram, "model");
        eogllDrawBufferObject(&bufferObject, GL_TRIANGLES);

        eogllSwapBuffers(window);
        eogllPollEvents(window);
    }
}