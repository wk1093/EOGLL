#include "hogll/window.hpp"

namespace ogl {
    Window::Window(int width, int height, const char* title, WindowHints hints) {
        if (eogllInit() != EOGLL_SUCCESS) {
            EOGLL_LOG_FATAL(stderr, "Failed to initialize EOGLL");
            exit(1);
        }
        window = eogllCreateWindow(width, height, title, hints.hints);
        if (window == nullptr) {
            EOGLL_LOG_FATAL(stderr, "Failed to create window");
            exit(1);
        }
    }
    Window::~Window() {
        eogllDestroyWindow(window);
        eogllTerminate();
    }

    void Window::swapBuffers() {
        eogllSwapBuffers(window);
    }

    void Window::pollEvents() {
        eogllPollEvents(window);
    }

    int Window::getWidth() {
        return window->width;
    }

    int Window::getHeight() {
        return window->height;
    }


    EogllWindow* Window::getWindow() {
        return window;
    }
    
    bool& Window::keyDown(int key) {
        return window->isDown[key];
    }

    bool& Window::keyPressed(int key) {
        return window->press[key];
    }

    bool& Window::keyReleased(int key) {
        return window->release[key];
    }

    bool& Window::mouseDown(int button) {
        return window->mouseIsDown[button];
    }

    bool& Window::mousePressed(int button) {
        return window->mousePress[button];
    }

    bool& Window::mouseReleased(int button) {
        return window->mouseRelease[button];
    }

    double& Window::mouseX() {
        return window->mousex;
    }

    double& Window::mouseY() {
        return window->mousey;
    }

    double& Window::mouseScrollX() {
        return window->mouseScrollx;
    }

    double& Window::mouseScrollY() {
        return window->mouseScrolly;
    }

    double& Window::mouseDeltaX() {
        return window->mousedx;
    }
    
    double& Window::mouseDeltaY() {
        return window->mousedy;
    }

    bool Window::shouldClose() {
        return eogllWindowShouldClose(window);
    }
}