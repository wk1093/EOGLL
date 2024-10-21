#include "hogll.hpp"

int main() {
    ogl::Window* window = new ogl::Window(800, 600, "HOGLL: PBR");

    eogllEnableDepth();

    EogllShaderProgram* shaderProgram = eogllLinkProgramFromFile("resources/shaders/pbr_vert.glsl", "resources/shaders/pbr_frag.glsl");

    ogl::Model model;
    model.rotate(45.0f, {0.0f, 1.0f, 0.0f}); // rotate 45 degrees on y axis

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

    ogl::Camera camera;

    camera.pos() = {0.0f, 0.0f, 5.0f};

    ogl::Projection projection(45.0f, 0.01f, 100000.0f);

    // ogl::BufferObject bufferObject("resources/models/cube.obj", {
    //     {GL_FLOAT, 3, EOGLL_ATTR_POSITION},
    //     {GL_FLOAT, 3, EOGLL_ATTR_NORMAL},
    //     {GL_FLOAT, 2, EOGLL_ATTR_TEXTURE}
    // });

    ogl::RenderModel obj("resources/models/cube.obj", {
        {GL_FLOAT, 3, ogl::POSITION},
        {GL_FLOAT, 3, ogl::NORMAL},
        {GL_FLOAT, 2, ogl::TEXTURE}
    });

    double speed = 1.0;
    double lastSpeed = 0.0;

    double moveSpeed = 1.0;
    double sensitivity = 0.1;

    bool mouseDisabled = false;

    while (!window->shouldClose()) {
        model.rotate(50.0f, {5.2f*window->dt()*speed, 10.0f*window->dt()*speed, 1.23f*window->dt()*speed});

        if (window->keyDown(EOGLL_KEY_LEFT)) {
            speed -= window->dt()*5;
        }
        if (window->keyDown(EOGLL_KEY_RIGHT)) {
            speed += window->dt()*5;
        }
        if (window->keyDown(EOGLL_KEY_UP)) {
            moveSpeed += window->dt()*5;
        }
        if (window->keyDown(EOGLL_KEY_DOWN)) {
            moveSpeed -= window->dt()*5;
        }
        if (window->keyPressed(EOGLL_KEY_E)) {
            if (lastSpeed == 0.0) {
                lastSpeed = speed;
                speed = 0.0;
            } else {
                speed = lastSpeed;
                lastSpeed = 0.0;
            }
        }

        if (window->keyDown(EOGLL_KEY_W)) {
            camera.move(EOGLL_FORWARD, window->dt()*moveSpeed);
        }
        if (window->keyDown(EOGLL_KEY_S)) {
            camera.move(EOGLL_BACKWARD, window->dt()*moveSpeed);
        }
        if (window->keyDown(EOGLL_KEY_A)) {
            camera.move(EOGLL_LEFT, window->dt()*moveSpeed);
        }
        if (window->keyDown(EOGLL_KEY_D)) {
            camera.move(EOGLL_RIGHT, window->dt()*moveSpeed);
        }
        if (window->keyDown(EOGLL_KEY_LEFT_SHIFT)) {
            camera.move(EOGLL_DOWN, window->dt()*moveSpeed);
        }
        if (window->keyDown(EOGLL_KEY_SPACE)) {
            camera.move(EOGLL_UP, window->dt()*moveSpeed);
        }

        if (window->mouseDown(EOGLL_MOUSE_BUTTON_LEFT)) {
            if (!mouseDisabled) {
                mouseDisabled = true;
                window->setCursorMode(EOGLL_CURSOR_DISABLED);
            }
        }
        if (window->keyDown(EOGLL_KEY_ESCAPE)) {
            if (mouseDisabled) {
                mouseDisabled = false;
                window->setCursorMode(EOGLL_CURSOR_NORMAL);
            }
        }

        if (mouseDisabled) {
            if (window->mouseDeltaX() != 0) {
                camera.yaw(window->mouseDeltaX() * sensitivity);
                window->mouseDeltaX() = 0;
            }
            if (window->mouseDeltaY() != 0) {
                camera.pitch(-window->mouseDeltaY() * sensitivity);
                window->mouseDeltaY() = 0;
            }
        }
        
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f); // clear color buffer
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // clear depth buffer

        // eogllUseProgram(shaderProgram);
        // camera.update(shaderProgram);
        // projection.update(shaderProgram, *window);
        // model.update(shaderProgram);
        // eogllSetUniform3fl(shaderProgram, "lights", lights, 2);
        // eogllSetUniform3fl(shaderProgram, "lightColors", lightColors, 2);
        // eogllBindTextureUniform(albedo, shaderProgram, "albedo", 0);
        // eogllBindTextureUniform(normal, shaderProgram, "normal", 1);
        // eogllBindTextureUniform(metallic, shaderProgram, "metallic", 2);
        // eogllBindTextureUniform(roughness, shaderProgram, "roughness", 3);
        // eogllBindTextureUniform(ao, shaderProgram, "ao", 4);
        // eogllSetUniform3fv(shaderProgram, "viewPos", *(vec3*)camera.posptr());
        // bufferObject.draw(GL_TRIANGLES);

        obj.draw(shaderProgram, [&](EogllShaderProgram* s) {
            camera.update(s);
            projection.update(s, *window);
            model.update(s);
            eogllSetUniform3fl(s, "lights", lights, 2);
            eogllSetUniform3fl(s, "lightColors", lightColors, 2);
            eogllBindTextureUniform(albedo, s, "albedo", 0);
            eogllBindTextureUniform(normal, s, "normal", 1);
            eogllBindTextureUniform(metallic, s, "metallic", 2);
            eogllBindTextureUniform(roughness, s, "roughness", 3);
            eogllBindTextureUniform(ao, s, "ao", 4);
            eogllSetUniform3fv(s, "viewPos", *(vec3*)camera.posptr());
        });

        window->swapBuffers();
        window->pollEvents();
    }
}