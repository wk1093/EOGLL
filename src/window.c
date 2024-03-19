#include "eogll/window.h"

#include "eogll/logging.h"
#include "eogll/input.h"

void eogllFramebufferSizeCallback(GLFWwindow* window, int width, int height) {
    EOGLL_LOG_TRACE(stdout, "\n");
    EOGLL_LOG_DEBUG(stdout, "Framebuffer size changed to %dx%d\n", width, height);
    glViewport(0, 0, width, height);

    EogllWindow* eogllWindow = (EogllWindow*)glfwGetWindowUserPointer(window);
    eogllWindow->width = (uint32_t)width;
    eogllWindow->height = (uint32_t)height;
}

void eogllWindowKeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods) {
    EOGLL_LOG_TRACE(stdout, "%d %d %d %d\n", key, scancode, action, mods);
    EogllWindow* eogllWindow = (EogllWindow*)glfwGetWindowUserPointer(window);
    if (eogllWindow == NULL) {
        EOGLL_LOG_ERROR(stderr, "eogllWindow is NULL\n");
        return;
    }
    if (action == EOGLL_PRESS) {
        eogllWindow->press[key] = true;
        eogllWindow->isDown[key] = true;
    } else if (action == EOGLL_RELEASE) {
        eogllWindow->release[key] = true;
        eogllWindow->isDown[key] = false;
    }
}

void eogllWindowMouseButtonCallback(GLFWwindow* window, int button, int action, int mods) {
    EOGLL_LOG_TRACE(stdout, "%d %d %d\n", button, action, mods);
    EogllWindow* eogllWindow = (EogllWindow*)glfwGetWindowUserPointer(window);
    if (eogllWindow == NULL) {
        EOGLL_LOG_ERROR(stderr, "eogllWindow is NULL\n");
        return;
    }
    if (action == EOGLL_PRESS) {
        eogllWindow->mousePress[button] = true;
        eogllWindow->mouseIsDown[button] = true;
    } else if (action == EOGLL_RELEASE) {
        eogllWindow->mouseRelease[button] = true;
        eogllWindow->mouseIsDown[button] = false;
    }
}

void eogllWindowCursorPosCallback(GLFWwindow* window, double xpos, double ypos) {
    EOGLL_LOG_TRACE(stdout, "%f %f\n", xpos, ypos);
    EogllWindow* eogllWindow = (EogllWindow*)glfwGetWindowUserPointer(window);
    if (eogllWindow == NULL) {
        EOGLL_LOG_ERROR(stderr, "eogllWindow is NULL\n");
        return;
    }

    eogllWindow->mousedx += xpos - eogllWindow->mousex; // we add to it incase there is multiple mouse movements in one frame (we want to keep track of the total movement)
    eogllWindow->mousedy += ypos - eogllWindow->mousey;
    eogllWindow->mousex = xpos;
    eogllWindow->mousey = ypos;
}

void eogllWindowScrollCallback(GLFWwindow* window, double xoffset, double yoffset) {
    EOGLL_LOG_TRACE(stdout, "%f %f\n", xoffset, yoffset);
    EogllWindow* eogllWindow = (EogllWindow*)glfwGetWindowUserPointer(window);
    if (eogllWindow == NULL) {
        EOGLL_LOG_ERROR(stderr, "eogllWindow is NULL\n");
        return;
    }

    eogllWindow->mouseScrollx = xoffset;
    eogllWindow->mouseScrolly = yoffset;
}

void eogllWindowFocusCallback(GLFWwindow* window, int focused) {
    EOGLL_LOG_DEBUG(stdout, "%d\n", focused);
    EogllWindow* eogllWindow = (EogllWindow*)glfwGetWindowUserPointer(window);
    if (eogllWindow == NULL) {
        EOGLL_LOG_ERROR(stderr, "eogllWindow is NULL\n");
        return;
    }

    eogllWindow->focused = focused;
}

EogllWindowHints eogllCreateWindowHints(bool resizable, bool decorated, bool floating, bool maximized, bool visible, bool focused, bool transparent) {
    EogllWindowHints hints;
    hints.resizable = resizable;
    hints.decorated = decorated;
    hints.floating = floating;
    hints.maximized = maximized;
    hints.visible = visible;
    hints.focused = focused;
    hints.transparent = transparent;
    return hints;
}

EogllWindowHints eogllDefaultWindowHints() {
    return eogllCreateWindowHints(true, true, false, false, true, true, false);
}

EogllWindow* eogllCreateWindow(uint32_t width, uint32_t height, const char* title, EogllWindowHints hints) {
    EOGLL_LOG_TRACE(stdout, "%s %dx%d %d %d %d %d %d %d\n", title, width, height, resizable, decorated, floating, maximized, visible, focused);

    EogllWindow* window = (EogllWindow*)malloc(sizeof(EogllWindow));
    if (!window) {
        EOGLL_LOG_ERROR(stderr, "Failed to allocate memory for window\n");
        return NULL;
    }
    window->width = width;
    window->height = height;
    EOGLL_LOG_TRACE(stdout, "%d keys, %d mouse buttons\n", EOGLL_KEY_LAST + 1, EOGLL_MOUSE_BUTTON_LAST + 1);
    for (int i = 0; i < EOGLL_KEY_LAST + 1; i++) {
        window->press[i] = false;
        window->release[i] = false;
        window->isDown[i] = false;
    }
    for (int i = 0; i < EOGLL_MOUSE_BUTTON_LAST + 1; i++) {
        window->mousePress[i] = false;
        window->mouseRelease[i] = false;
        window->mouseIsDown[i] = false;
    }
    window->mousedx = 0;
    window->mousedy = 0;
    window->mouseScrollx = 0;
    window->mouseScrolly = 0;
    window->focused = hints.focused;
    glfwWindowHint(GLFW_RESIZABLE, hints.resizable);
    glfwWindowHint(GLFW_DECORATED, hints.decorated);
    glfwWindowHint(GLFW_FLOATING, hints.floating);
    glfwWindowHint(GLFW_MAXIMIZED, hints.maximized);
    glfwWindowHint(GLFW_VISIBLE, hints.visible);
    glfwWindowHint(GLFW_FOCUSED, hints.focused);
    glfwWindowHint(GLFW_TRANSPARENT_FRAMEBUFFER, hints.transparent);
    // 330 core
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GLFW_TRUE);
#endif

    window->window = glfwCreateWindow((int)width, (int)height, title, NULL, NULL);
    glfwSetWindowUserPointer(window->window, window);
    glfwSetFramebufferSizeCallback(window->window, eogllFramebufferSizeCallback);

    if (!window->window) {
        EOGLL_LOG_ERROR(stderr, "Failed to create window\n");
        char* description;
        int g = glfwGetError((const char **) &description);
        EOGLL_LOG_ERROR(stderr, "GLFW Error %d: %s\n", g, description);

        return NULL;
    }
    glfwSetFramebufferSizeCallback(window->window, eogllFramebufferSizeCallback);
    glfwSetKeyCallback(window->window, eogllWindowKeyCallback);
    glfwSetMouseButtonCallback(window->window, eogllWindowMouseButtonCallback);
    glfwSetCursorPosCallback(window->window, eogllWindowCursorPosCallback);
    glfwSetScrollCallback(window->window, eogllWindowScrollCallback);
    glfwSetWindowFocusCallback(window->window, eogllWindowFocusCallback);
    glfwMakeContextCurrent(window->window);
    if (!gladLoadGL(glfwGetProcAddress)) {
        EOGLL_LOG_ERROR(stderr, "Failed to load OpenGL\n");
        return NULL;
    }
    glfwGetCursorPos(window->window, &window->mousex, &window->mousey);
    EOGLL_LOG_INFO(stdout, "%s %s\n", glGetString(GL_VENDOR), glGetString(GL_VERSION));
    EOGLL_LOG_INFO(stdout, "%s\n", glGetString(GL_RENDERER));
    int max;
    glGetIntegerv(GL_MAX_VERTEX_ATTRIBS, &max);
    EOGLL_LOG_INFO(stdout, "%d vertex attributes max\n", max);

    return window;

}

bool eogllWindowShouldClose(EogllWindow* window) {
    bool r = glfwWindowShouldClose(window->window);
    EOGLL_LOG_TRACE(stdout, "%d\n", r);
    return r;
}

void eogllSetWindowShouldClose(EogllWindow* window, bool shouldClose) {
    EOGLL_LOG_TRACE(stdout, "%d\n", shouldClose);
    glfwSetWindowShouldClose(window->window, shouldClose);
}

void eogllPollEvents(EogllWindow* window) {
    EOGLL_LOG_TRACE(stdout, "\n");

    for (int i = 0; i < EOGLL_KEY_LAST + 1; i++) {
        window->press[i] = false;
        window->release[i] = false;
    }
    for (int i = 0; i < EOGLL_MOUSE_BUTTON_LAST + 1; i++) {
        window->mousePress[i] = false;
        window->mouseRelease[i] = false;
    }
    window->mousedx = 0;
    window->mousedy = 0;
    glfwPollEvents();
}

void eogllSwapBuffers(EogllWindow* window) {
    EOGLL_LOG_TRACE(stdout, "\n");
    glfwSwapBuffers(window->window);
}

void eogllDestroyWindow(EogllWindow* window) {
    EOGLL_LOG_TRACE(stdout, "\n");
    glfwDestroyWindow(window->window);
    free(window);
}

bool eogllGetKeyPress(EogllWindow* window, int key) {
    bool r = window->press[key];
    EOGLL_LOG_TRACE(stdout, "%d %d\n", key, r);
    return r;
}

bool eogllGetKeyRelease(EogllWindow* window, int key) {
    bool r = window->release[key];
    EOGLL_LOG_TRACE(stdout, "%d %d\n", key, r);
    return r;
}

bool eogllGetKeyIsDown(EogllWindow* window, int key) {
    bool r = window->isDown[key];
    EOGLL_LOG_TRACE(stdout, "%d %d\n", key, r);
    return r;
}

bool eogllGetMousePress(EogllWindow* window, int button) {
    bool r = window->mousePress[button];
    EOGLL_LOG_TRACE(stdout, "%d %d\n", button, r);
    return r;
}

bool eogllGetMouseRelease(EogllWindow* window, int button) {
    bool r = window->mouseRelease[button];
    EOGLL_LOG_TRACE(stdout, "%d %d\n", button, r);
    return r;
}

bool eogllGetMouseIsDown(EogllWindow* window, int button) {
    bool r = window->mouseIsDown[button];
    EOGLL_LOG_TRACE(stdout, "%d %d\n", button, r);
    return r;
}

void eogllGetMousePos(EogllWindow* window, double* xpos, double* ypos) {
    *xpos = window->mousex;
    *ypos = window->mousey;
}

void eogllSetMousePos(EogllWindow* window, double xpos, double ypos) {
    EOGLL_LOG_TRACE(stdout, "%f %f\n", xpos, ypos);
    glfwSetCursorPos(window->window, xpos, ypos);
    window->mousex = xpos;
    window->mousey = ypos;
}

void eogllGetMouseDelta(EogllWindow* window, double* dxpos, double* dypos) {
    *dxpos = window->mousedx;
    *dypos = window->mousedy;
}

void eogllGetMouseScroll(EogllWindow* window, double* xscroll, double* yscroll) {
    *xscroll = window->mouseScrollx;
    *yscroll = window->mouseScrolly;
}

void eogllGetWindowSize(EogllWindow* window, uint32_t* width, uint32_t* height) {
    *width = window->width;
    *height = window->height;
}

void eogllSetWindowSize(EogllWindow* window, uint32_t width, uint32_t height) {
    EOGLL_LOG_TRACE(stdout, "%dx%d\n", width, height);
    glfwSetWindowSize(window->window, (int)width, (int)height);
    window->width = width;
    window->height = height;
}

void eogllGetWindowPos(EogllWindow* window, int* xpos, int* ypos) {
    glfwGetWindowPos(window->window, xpos, ypos);
}

void eogllSetWindowPos(EogllWindow* window, int xpos, int ypos) {
    EOGLL_LOG_TRACE(stdout, "%d %d\n", xpos, ypos);
    glfwSetWindowPos(window->window, xpos, ypos);
}

void eogllGetCursorPos(EogllWindow* window, double* xpos, double* ypos) {
    glfwGetCursorPos(window->window, xpos, ypos);
}

void eogllSetCursorPos(EogllWindow* window, double xpos, double ypos) {
    EOGLL_LOG_TRACE(stdout, "%f %f\n", xpos, ypos);
    glfwSetCursorPos(window->window, xpos, ypos);
    window->mousex = xpos;
    window->mousey = ypos;
}

static inline int inl_max(int a , int b )
{
    return a > b ? a : b;
}

static inline int inl_min( int a , int b )
{
    return a < b ? a : b;
}

bool glfwSetWindowCenter(GLFWwindow *window) {
    if(!window)
        return false;

    int sx = 0, sy = 0;
    int px = 0, py = 0;
    int mx = 0, my = 0;
    int monitor_count = 0;
    int best_area = 0;
    int final_x = 0, final_y = 0;

    glfwGetWindowSize(window, &sx, &sy);
    glfwGetWindowPos(window, &px, &py);

    // Iterate throug all monitors
    GLFWmonitor **m = glfwGetMonitors(&monitor_count);
    if(!m)
        return false;

    for(int j = 0; j < monitor_count; ++j) {

        glfwGetMonitorPos( m[j] , &mx, &my );
        const GLFWvidmode * mode = glfwGetVideoMode( m[j] );
        if( !mode )
            continue;

        // Get intersection of two rectangles - screen and window
        int minX = inl_max(mx, px);
        int minY = inl_max(my, py);

        int maxX = inl_min(mx+mode->width, px+sx);
        int maxY = inl_min(my+mode->height, py+sy);

        // Calculate area of the intersection
        int area = inl_max(maxX - minX, 0) * inl_max(maxY - minY, 0);

        // If its bigger than actual (window covers more space on this monitor)
        if(area > best_area)
        {
            // Calculate proper position in this monitor
            final_x = mx + (mode->width-sx)/2;
            final_y = my + (mode->height-sy)/2;

            best_area = area;
        }

    }

    // We found something
    if(best_area)
        glfwSetWindowPos(window, final_x, final_y);

        // Something is wrong - current window has NOT any intersection with any monitors. Move it to the default one.
    else {
        GLFWmonitor * primary = glfwGetPrimaryMonitor();
        if(primary) {
            const GLFWvidmode *desktop = glfwGetVideoMode(primary);

            if(desktop)
                glfwSetWindowPos(window, (desktop->width-sx)/2, (desktop->height-sy)/2);
            else
                return false;
        }
        else
            return false;
    }

    return true;
}

void eogllCenterWindow(EogllWindow* window) {
    glfwSetWindowCenter(window->window);
}

void eogllSetCursorMode(EogllWindow* window, int mode) {
    glfwSetInputMode(window->window, GLFW_CURSOR, mode);
}