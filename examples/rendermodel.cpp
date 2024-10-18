#include <hogll.hpp>

int main() {
    ogl::Window window(800, 600, "HOGLL: Model Loading");

    eogllEnableDepth();
    eogllEnableFaceCulling();
    // glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

    ogl::ObjectAttrs attrs = ogl::ObjectAttrs{
        {GL_FLOAT, 3, EOGLL_ATTR_POSITION},
        {GL_FLOAT, 3, EOGLL_ATTR_NORMAL}
    };

    ogl::RenderModel cube("resources/models/cube.fbx", attrs);


    // really cool system that allows us to have default shaders that work for most attribute cases
    // these shader are generated at runtime and are not saved to disk
    // if you just give it position, it will be a flat single color shader, 
    // but if you give it the normal, it will add very simple shading (static directional lighting)

    EogllShaderProgram* shader = ogl::basicShaderGenerator(attrs, true);


    ogl::Model model;
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