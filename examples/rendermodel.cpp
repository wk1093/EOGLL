#include <hogll.hpp>

inline int min(int a, int b) {
    return a < b ? a : b;
}

int main() {
    srand(time(NULL));
    ogl::Window window(800, 600, "HOGLL: Model Loading");

    eogllEnableDepth();
    // eogllEnableFaceCulling();

    ogl::ModelAttrs attrs = ogl::ModelAttrs {
        {GL_FLOAT, 3, ogl::POSITION},
        {GL_FLOAT, 3, ogl::NORMAL},
        {GL_FLOAT, 2, ogl::TEXTURE},
        {GL_INT, 4, ogl::BONE_IDS},
        {GL_FLOAT, 4, ogl::BONE_WEIGHTS}
    };

    ogl::RenderModel cube("resources/models/Main_Char_2_Anim.fbx", attrs, "../textures/");


    EogllShaderProgram* shader = eogllLinkProgramFromFile("resources/shaders/model.vert", "resources/shaders/model.frag");


    ogl::Model model;
    model.scale() = {0.01f, 0.01f, 0.01f};
    ogl::Camera camera;
    ogl::Projection projection(45.0f, 0.1f, 100.0f);
    // ogl::Projection projection(0.1f, 100.0f);

    camera.pos() = {0.0f, 0.0f, 10.0f};

    model.rot() = {0.0f, 0.0f, 0.0f};
    model.pos() = {0.0f, -10.0f, 0.0f};

    double speed = 1.0;
    double lastSpeed = 0.0;

    double moveSpeed = 1.0;
    double sensitivity = 0.1;

    bool mouseDisabled = false;

    while (!window.shouldClose()) {
        if (window.keyDown(EOGLL_KEY_LEFT)) {
            speed -= window.dt()*5;
        }
        if (window.keyDown(EOGLL_KEY_RIGHT)) {
            speed += window.dt()*5;
        }
        if (window.keyDown(EOGLL_KEY_UP)) {
            moveSpeed += window.dt()*5;
        }
        if (window.keyDown(EOGLL_KEY_DOWN)) {
            moveSpeed -= window.dt()*5;
        }
        if (window.keyPressed(EOGLL_KEY_E)) {
            if (lastSpeed == 0.0) {
                lastSpeed = speed;
                speed = 0.0;
            } else {
                speed = lastSpeed;
                lastSpeed = 0.0;
            }
        }

        if (window.keyDown(EOGLL_KEY_W)) {
            camera.move(EOGLL_FORWARD, window.dt()*moveSpeed);
        }
        if (window.keyDown(EOGLL_KEY_S)) {
            camera.move(EOGLL_BACKWARD, window.dt()*moveSpeed);
        }
        if (window.keyDown(EOGLL_KEY_A)) {
            camera.move(EOGLL_LEFT, window.dt()*moveSpeed);
        }
        if (window.keyDown(EOGLL_KEY_D)) {
            camera.move(EOGLL_RIGHT, window.dt()*moveSpeed);
        }
        if (window.keyDown(EOGLL_KEY_LEFT_SHIFT)) {
            camera.move(EOGLL_DOWN, window.dt()*moveSpeed);
        }
        if (window.keyDown(EOGLL_KEY_SPACE)) {
            camera.move(EOGLL_UP, window.dt()*moveSpeed);
        }

        if (window.mouseDown(EOGLL_MOUSE_BUTTON_LEFT)) {
            if (!mouseDisabled) {
                mouseDisabled = true;
                window.setCursorMode(EOGLL_CURSOR_DISABLED);
            }
        }
        if (window.keyDown(EOGLL_KEY_ESCAPE)) {
            if (mouseDisabled) {
                mouseDisabled = false;
                window.setCursorMode(EOGLL_CURSOR_NORMAL);
            }
        }

        if (mouseDisabled) {
            if (window.mouseDeltaX() != 0) {
                camera.yaw(window.mouseDeltaX() * sensitivity);
                window.mouseDeltaX() = 0;
            }
            if (window.mouseDeltaY() != 0) {
                camera.pitch(-window.mouseDeltaY() * sensitivity);
                window.mouseDeltaY() = 0;
            }
        }

        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // model.pos() = {0.0f, 0.0f, 0.1f*sin(glfwGetTime()) * 5.0f};
        // model.rot() = {glfwGetTime()*8, glfwGetTime()*10, 0.0f};

        // finalBonesMatrices
        // we will try something, by adding some random matrices to the bones
        // for (int i = 0; i < 100; i++) {
        //     std::string name = "finalBonesMatrices[" + std::to_string(i) + "]";
        //     mat4 mat = {};
        //     glm_mat4_identity(mat);
        //     for (int j = 0; j < 4; j++) {
        //         for (int k = 0; k < 4; k++) {
        //             mat[j][k] = (float)rand() / RAND_MAX;
        //         }
        //     }
        //     eogllSetUniformMatrix4fv(shader, name.c_str(), mat);
        // }

        cube.draw(shader, [&](EogllShaderProgram* s) {
            model.update(s);
            camera.update(s);
            projection.update(s, window);
        });

        window.swapBuffers();
        window.pollEvents();
    }
}