# HOGLL (High-level OpenGL Library)

HOGLL is a high(ish)-level OpenGL library in ***C++*** (unlike EOGLL which is ***C***), that is a wrapper around EOGLL. It is designed to be easier to use than EOGLL, and to make it easier to use OpenGL in C++.

## Usage
### Installation
HOGLL is a part of a CMake project (EOGLL), so you can use it as a subdirectory in your project. Using FetchContent is recommended.

This can be done by adding the following to your CMakeLists.txt:
```cmake
include(FetchContent)
FetchContent_Declare(
        eogll
        GIT_REPOSITORY https://github.com/wk1093/EOGLL.git
        GIT_TAG master
)
FetchContent_MakeAvailable(eogll)

target_link_libraries(YOUR_TARGET_HERE hogll)
```

### Example
```cpp
#include "hogll.hpp"
int main() {
    ogl::Window window(800, 600, "EOGLL: HOGLL Window");
    
    // normally you would need to create a shader program, but HOGLL will create a basic default one
    // the default will ONLY work if you just have a single 3f position attribute, otherwise you will need to create your own shader
    // the default shader also doesn't work with uniforms like model, view, or projection
    // it is mostly for testing purposes
    ogl::ObjectAttrs attrs = ogl::ObjectAttrs{{GL_FLOAT, 3, EOGLL_ATTR_POSITION}};
    ogl::BufferObject cube("resources/models/cube.obj", attrs);

    while (!window.shouldClose()) {
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        cube.draw(GL_TRIANGLES);

        window.swapBuffers();
        window.pollEvents();
    }

    return 0;
}
```

## Documentation

Documentation is WIP.