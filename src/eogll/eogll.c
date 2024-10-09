#include "eogll.h"

void eogllGLFWErrorCallback(int error, const char* description) {
    EOGLL_LOG_TRACE(stdout, "\n");
    EOGLL_LOG_ERROR(stderr, "GLFW Error %d: %s\n", error, description);
}

bool __eogll_is_initialized = false;

EogllResult eogllInit() {
    EOGLL_LOG_TRACE(stdout, "\n");
    if (__eogll_is_initialized) {
        return EOGLL_SUCCESS;
    }
    __eogll_is_initialized = true;
    if (!glfwInit()) {
        return EOGLL_FAILURE;
    }
    glfwSetErrorCallback(eogllGLFWErrorCallback);
    EOGLL_LOG_INFO(stdout, "%s\n", eogllGetVersionString());
    EOGLL_LOG_INFO(stdout, "GLFW %s\n", glfwGetVersionString());

    return EOGLL_SUCCESS;
}

void eogllTerminate() {
    EOGLL_LOG_TRACE(stdout, "\n");
    if (!__eogll_is_initialized) {
        return;
    }
    __eogll_is_initialized = false;
    glfwTerminate();
    EOGLL_LOG_INFO(stdout, "Bye!\n");
}