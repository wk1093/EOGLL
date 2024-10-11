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
        WindowHints(bool resizable, bool decorated, bool floating, bool maximized, bool visible, bool focused, bool transparent) {
            hints = eogllCreateWindowHints(resizable, decorated, floating, maximized, visible, focused, transparent);
        }
        WindowHints() {
            hints = eogllDefaultWindowHints();
        }
    };

    struct Window {
    private:
        EogllWindow* window;
        EogllShaderProgram* defaultShader3f_p;
    public:

        Window(int width, int height, const char* title, WindowHints hints=WindowHints());
        ~Window();

        void swapBuffers();
        void pollEvents();

        int getWidth() const;
        int getHeight() const;
        double dt() const;

        EogllWindow* getWindow();

        bool& keyDown(int key);
        bool& keyPressed(int key);
        bool& keyReleased(int key);

        bool& mouseDown(int button);
        bool& mousePressed(int button);
        bool& mouseReleased(int button);

        double& mouseX();
        double& mouseY();
        double& mouseScrollX();
        double& mouseScrollY();
        double& mouseDeltaX();
        double& mouseDeltaY();

        bool shouldClose();

        void setCursorMode(int mode);
    };
}

#endif