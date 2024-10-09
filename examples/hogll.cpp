#include <hogll.hpp>

int main() {
    ogl::Window window(800, 600, "EOGLL: HOGLL Window");
    while (!window.shouldClose()) {
        window.swapBuffers();
        window.pollEvents();
    }
}