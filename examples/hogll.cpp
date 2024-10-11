#include <hogll.hpp>

int main() {
    ogl::Window window(800, 600, "EOGLL: HOGLL Window");

    eogllEnableDepth();
    eogllEnableFaceCulling();

    ogl::ObjectAttrs attrs = ogl::ObjectAttrs{
        {GL_FLOAT, 3, EOGLL_ATTR_POSITION},
        {GL_FLOAT, 3, EOGLL_ATTR_NORMAL}
    };

    ogl::BufferObject cube("resources/models/dragon.obj", attrs);

    EogllShaderProgram* shader = eogllLinkProgramFromFile("resources/shaders/dragon_vertex.glsl", "resources/shaders/dragon_fragment.glsl");

    ogl::Model model;
    ogl::Camera camera;
    ogl::Projection projection(45.0f, 0.1f, 100.0f);

    camera.pos() = glm::vec3(0.0f, 0.0f, 5.0f);

    while (!window.shouldClose()) {
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        model.pos() = glm::vec3(0.0f, 0.0f, 0.1f*sin(glfwGetTime()) * 5.0f);
        model.rot() = glm::vec3(glfwGetTime()*8, glfwGetTime()*10, 0.0f);

        eogllUseProgram(shader);

        projection.update(shader, "projection", window);

        camera.update(shader, "view");
        model.update(shader, "model");
        cube.draw(GL_TRIANGLES);

        window.swapBuffers();
        window.pollEvents();
    }
}