#include <hogll.hpp>

int main() {
    ogl::Window window(800, 600, "Hello, world!");
    while (!window.shouldClose()) {
        window.swapBuffers();
        window.pollEvents();
    }
}