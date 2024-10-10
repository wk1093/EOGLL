#include <hogll.hpp>

int main() {
    ogl::Window window(800, 600, "EOGLL: HOGLL Window");

    eogllEnableDepth();
    // eogllEnableFaceCulling();

    EogllObjectAttrs attrs = eogllCreateObjectAttrs();
    eogllAddObjectAttr(&attrs, GL_FLOAT, 3, EOGLL_ATTR_POSITION);
    eogllAddObjectAttr(&attrs, GL_FLOAT, 3, EOGLL_ATTR_NORMAL);
    ogl::BufferObject cube("resources/models/cube.obj", attrs);

    EogllShaderProgram* shader = eogllLinkProgramFromFile("resources/shaders/dragon_vertex.glsl", "resources/shaders/dragon_fragment.glsl");

    EogllModel model = eogllCreateModel();
    EogllCamera camera = eogllCreateCamera();
    EogllProjection projection = eogllPerspectiveProjection(45.0f, 0.1f, 100.0f);

    glm_vec3_copy((vec3){0.0f, 0.0f, 5.0f}, camera.pos);

    while (!window.shouldClose()) {
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


        eogllUseProgram(shader);
        eogllUpdateCameraMatrix(&camera, shader, "view");
        eogllUpdateProjectionMatrix(&projection, shader, "projection", window.getWidth(), window.getHeight());
        eogllUpdateModelMatrix(&model, shader, "model");
        cube.draw(GL_TRIANGLES);

        window.swapBuffers();
        window.pollEvents();
    }
}