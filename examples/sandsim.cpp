#include "hogll.hpp"

int main() {
    ogl::WindowHints hints;
    hints.hints.resizable = false;
    ogl::Window* window = new ogl::Window(800, 600, "HOGLL: Sand Sim", hints);


    EogllShaderProgram* sandProcessor = eogllLinkProgramFromFile("resources/shaders/sand.vert", "resources/shaders/sand_p.frag");
    EogllShaderProgram* sandRenderer = eogllLinkProgramFromFile("resources/shaders/sand.vert", "resources/shaders/sand.frag");

    EogllFramebuffer* fbo0 = eogllCreateFramebuffer(800, 600);
    EogllFramebuffer* fbo1 = eogllCreateFramebuffer(800, 600);
    
    float vertices[] = {
        -1.0f, -1.0f, 0.0f,
        1.0f, -1.0f, 0.0f,
        1.0f, 1.0f, 0.0f,
        -1.0f, 1.0f, 0.0f
    };
    unsigned int indices[] = {
        0, 1, 2,
        2, 3, 0
    };
    ogl::ObjectAttrs attrs;
    attrs.add(GL_FLOAT, 3, EOGLL_ATTR_POSITION);
    GLuint vao = eogllGenVertexArray();
    GLuint vbo = eogllGenBuffer(vao, GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    GLuint ebo = eogllGenBuffer(vao, GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
    attrs.build(vao);
    ogl::BufferObject obj(vao, vbo, ebo, sizeof(indices), GL_UNSIGNED_INT);


    bool currentIs0 = true;

    glm::vec2 mouseClick;

    int mouseState = 0; // 0 = none, 1 = erase, 2 = sand, 3 = water

    float radius = 1.0f;

    while (!window->shouldClose()) {
        // TODO: implement input handling
        if (window->mouseDown(EOGLL_MOUSE_BUTTON_LEFT)) {
            mouseClick = {window->mouseX(), window->mouseY()};
        } else {
            mouseClick = {-1, -1};
        }

        if (window->keyPressed(EOGLL_KEY_1)) {
            mouseState = 1;
        }
        if (window->keyPressed(EOGLL_KEY_2)) {
            mouseState = 2;
        }
        if (window->keyPressed(EOGLL_KEY_3)) {
            mouseState = 3;
        }

        if (window->mouseScrollY() != 0) {
            radius += window->mouseScrollY() * 0.1f;
            window->mouseScrollY() = 0;
        }
        
        // Processing

        eogllUseProgram(sandProcessor);
        if (currentIs0) {
            eogllBindFramebuffer(fbo1);
            eogllBindTextureUniformi(fbo0->texture, sandProcessor, "sandTexture", 0);
        } else {
            eogllBindFramebuffer(fbo0);
            eogllBindTextureUniformi(fbo1->texture, sandProcessor, "sandTexture", 0);

        }
        currentIs0 = !currentIs0;
        eogllSetUniform2f(sandProcessor, "mouseClick", mouseClick.x, mouseClick.y);
        eogllSetUniform1f(sandProcessor, "time", eogllGetTime());
        eogllSetUniform1f(sandProcessor, "radius", radius);
        eogllSetUniform1i(sandProcessor, "mouseNum", mouseState);
        obj.draw(GL_TRIANGLES);

        glBindFramebuffer(GL_FRAMEBUFFER, 0);

        // Rendering
        
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        eogllUseProgram(sandRenderer);
        if (currentIs0) {
            glActiveTexture(GL_TEXTURE0);
            glBindTexture(GL_TEXTURE_2D, fbo1->texture);
            eogllSetUniform1i(sandRenderer, "sandTexture", 0);

        } else {
            glActiveTexture(GL_TEXTURE0);
            glBindTexture(GL_TEXTURE_2D, fbo0->texture);
            eogllSetUniform1i(sandRenderer, "sandTexture", 0);
        }
        obj.draw(GL_TRIANGLES);

        window->swapBuffers();
        window->pollEvents();
    }
}