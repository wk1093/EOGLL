/**
 * @file window.hpp
 * @brief HOGLL window header file
 * @date 2024-10-9
 *
 * HOGLL window header file
 */

#pragma once
#ifndef _HOGLL_WINDOW_HPP_
#define _HOGLL_WINDOW_HPP_

#include "pch.hpp"

namespace ogl {
    struct WindowHints {
        EogllWindowHints hints;
        WindowHints(bool resizable, bool decorated, bool floating, bool maximized, bool visible, bool focused, bool transparent);
        WindowHints();
    };

    struct Window {
    private:
        EogllWindow* window;
        EogllShaderProgram* defaultShader3f_p;
    public:
        inline Window(EogllWindow* ebo) : window(ebo) {}
        Window(int width, int height, const char* title, WindowHints hints=WindowHints());
        ~Window();

        void swapBuffers();
        void pollEvents();

        int getWidth() const;
        int getHeight() const;
        EOGLL_NO_DISCARD double dt() const;

        EogllWindow* getWindow();

        EOGLL_NO_DISCARD bool& keyDown(int key);
        EOGLL_NO_DISCARD bool& keyPressed(int key);
        EOGLL_NO_DISCARD bool& keyReleased(int key);

        EOGLL_NO_DISCARD bool& mouseDown(int button);
        EOGLL_NO_DISCARD bool& mousePressed(int button);
        EOGLL_NO_DISCARD bool& mouseReleased(int button);

        EOGLL_NO_DISCARD double& mouseX();
        EOGLL_NO_DISCARD double& mouseY();
        EOGLL_NO_DISCARD double& mouseScrollX();
        EOGLL_NO_DISCARD double& mouseScrollY();
        EOGLL_NO_DISCARD double& mouseDeltaX();
        EOGLL_NO_DISCARD double& mouseDeltaY();

        EOGLL_NO_DISCARD bool shouldClose();

        void setCursorMode(int mode);

        inline operator EogllWindow*() { return window; }
    };
}

#endif