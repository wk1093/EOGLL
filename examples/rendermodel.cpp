#include <hogll.hpp>

int main() {
    ogl::Window window(800, 600, "HOGLL: Model Loading");

    eogllEnableDepth();
    eogllEnableFaceCulling();

    ogl::ObjectAttrs attrs = ogl::ObjectAttrs{
        {GL_FLOAT, 3, EOGLL_ATTR_POSITION},
        {GL_FLOAT, 3, EOGLL_ATTR_NORMAL},
        {GL_FLOAT, 2, EOGLL_ATTR_TEXTURE}
    };

    ogl::RenderModel cube("resources/models/Soldier_Rig.fbx", attrs, "../textures/");


    EogllShaderProgram* shader = eogllLinkProgramFromFile("resources/shaders/model.vert", "resources/shaders/model.frag");


    ogl::Model model;
    model.scale() = {0.3f, 0.3f, 0.3f};
    ogl::Camera camera;
    ogl::Projection projection(45.0f, 0.1f, 100.0f);
    // ogl::Projection projection(0.1f, 100.0f);

    camera.pos() = {0.0f, 0.0f, 5.0f};

    while (!window.shouldClose()) {
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        model.pos() = {0.0f, 0.0f, 0.1f*sin(glfwGetTime()) * 5.0f};
        model.rot() = {glfwGetTime()*8, glfwGetTime()*10, 0.0f};

        // eogllUseProgram(shader);

        // projection.update(shader, "projection", window);
        // camera.update(shader, "view");
        // model.update(shader, "model");
        // cube.draw(GL_TRIANGLES);
        cube.draw(&window, shader, camera, projection, model);

        window.swapBuffers();
        window.pollEvents();
    }
}