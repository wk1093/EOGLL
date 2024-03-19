/**
 * @file window.h
 * @brief EOGLL window header file
 * @date 2024-01-28
 *
 * EOGLL window header file
 */

#pragma once
#ifndef _EOGLL_WINDOW_H_
#define _EOGLL_WINDOW_H_

#include "pch.h"
#include "input.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
* @brief A struct that represents a window
* @see eogllCreateWindow
* @see eogllDestroyWindow
*
* This struct is used to handle all window related things
*/
typedef EOGLL_DECL_STRUCT struct EogllWindow {
    /// The GLFW window
    GLFWwindow* window;
    /// The width of the window, this is updated whenever the window is resized
    uint32_t width;
    /// The height of the window, this is updated whenever the window is resized
    uint32_t height;

    /// An array of booleans that represents if a key was pressed
    bool press[EOGLL_KEY_LAST + 1];

    /// An array of booleans that represents if a key was released
    bool release[EOGLL_KEY_LAST + 1];

    /// An array of booleans that represents if a key is down
    bool isDown[EOGLL_KEY_LAST + 1];

    /// An array of booleans that represents if a mouse button was pressed
    bool mousePress[EOGLL_MOUSE_BUTTON_LAST + 1];

    /// An array of booleans that represents if a mouse button was released
    bool mouseRelease[EOGLL_MOUSE_BUTTON_LAST + 1];

    /// An array of booleans that represents if a mouse button is down
    bool mouseIsDown[EOGLL_MOUSE_BUTTON_LAST + 1];

    /// The x position of the mouse
    double mousex;

    /// The x delta of the mouse
    double mousedx;

    /// The y position of the mouse
    double mousey;

    /// The y delta of the mouse
    double mousedy;

    /// The x scroll of the mouse
    double mouseScrollx;

    /// The y scroll of the mouse
    double mouseScrolly;

    /// whether or not the window is focused
    bool focused;

    // TODO: add more window properties
} EogllWindow;

/**
 * @brief A struct that holds all the extra data to create a window
 * @see eogllCreateWindow
 * @see eogllDefaultWindowHints
 * @see eogllCreateWindowHints
 *
 * This struct is used to create a window with window "hints"
 */
typedef EOGLL_DECL_STRUCT struct EogllWindowHints {
    /// Whether or not the window can be resized
    bool resizable;

    /// Whether or not the window has a border and title bar
    bool decorated;

    /// Whether or not the window is floating (always on top)
    bool floating;

    /// Whether or not the window is maximized
    bool maximized;

    /// Whether or not the window is visible
    bool visible;

    /// Whether or not the window is focused (this is only the starting state, the window can go in and out of focus later)
    bool focused;
} EogllWindowHints;

/**
 * @brief Creates a window hints struct
 * @param resizable Whether or not the window can be resized
 * @param decorated Whether or not the window has a border and title bar
 * @param floating Whether or not the window is floating (always on top)
 * @param maximized Whether or not the window is maximized
 * @param visible Whether or not the window is visible
 * @param focused Whether or not the window is focused (this is only the starting state, the window can go in and out of focus later)
 * @return The created window hints struct
 * @see eogllDefaultWindowHints
 * @see EogllWindowHints
 *
 * This function creates a window hints struct with the given values
 */
EOGLL_DECL_FUNC_ND EogllWindowHints eogllCreateWindowHints(bool resizable, bool decorated, bool floating, bool maximized, bool visible, bool focused);

/**
 * @brief Creates a window hints struct with default values
 * @return The created window hints struct
 * @see eogllCreateWindowHints
 * @see EogllWindowHints
 *
 * This function creates a window hints struct with the following values:
 * resizable: true
 * decorated: true
 * floating: false
 * maximized: false
 * visible: true
 * focused: true
 */
EOGLL_DECL_FUNC_ND EogllWindowHints eogllDefaultWindowHints();

/**
 * @brief Creates a window
 * @param width The width of the window
 * @param height The height of the window
 * @param title The title of the window
 * @param hints The window hints to use
 * @return The created window
 * @see eogllDestroyWindow
 * @see EogllWindow
 * @see EogllWindowHints
 *
 * This function creates a window with the given width, height, title, and window hints
 */
EOGLL_DECL_FUNC_ND EogllWindow* eogllCreateWindow(uint32_t width, uint32_t height, const char* title, EogllWindowHints hints);

/**
 * @brief Checks if the window should close
 * @param window The window to check
 * @return Whether or not the window should close
 * @see eogllSetWindowShouldClose
 *
 * This function checks if the window should close (normally this is when the user clicks the close button).
 * Most programs will have a loop that looks something like this:
 * @code{.c}
 * while (!eogllWindowShouldClose(window)) {
 *    // do stuff
 *    eogllPollEvents(window);
 *    eogllSwapBuffers(window);
 * }
 * @endcode
 */
EOGLL_DECL_FUNC_ND bool eogllWindowShouldClose(EogllWindow* window);

/**
 * @brief Sets whether or not the window should close
 * @param window The window to set
 * @param shouldClose Whether or not the window should close
 * @see eogllWindowShouldClose
 *
 * This function is mostly used when you want to exit the program, but you don't want to have to repeat all of the cleanup code:
 * @code{.c}
 * while (!eogllWindowShouldClose(window)) {
 *     // do stuff
 *     if (shouldExit) {
 *         eogllSetWindowShouldClose(window, true);
 *     }
 *     // rest of loop
 * }
 * // cleanup code HERE in one place
 * // delete stuff (buffers, shaders, window, etc.)
 *
 * @endcode
 *
 * Instead of doing this:
 * @code{.c}
 * while (!eogllWindowShouldClose(window)) {
 *     // do stuff
 *     if (shouldExit) {
 *         // cleanup code HERE
 *         // delete stuff (buffers, shaders, window, etc.)
 *         return 0;
 *     }
 *     // rest of loop
 * }
 * // repeated cleanup code
 * // delete stuff (buffers, shaders, window, etc.)
 * @endcode
 */
EOGLL_DECL_FUNC void eogllSetWindowShouldClose(EogllWindow* window, bool shouldClose);

/**
 * @brief Polls events
 * @param window The window to poll events for
 * @see eogllWindowShouldClose
 * @see eogllSwapBuffers
 *
 * This function polls events for the given window.
 * This function should be called every frame.
 *
 * This function is used to update the window's properties (such as the width and height) and to update the input.
 */
EOGLL_DECL_FUNC void eogllPollEvents(EogllWindow* window);

/**
 * @brief Swaps the buffers
 * @param window The window to swap the buffers for
 * @see eogllWindowShouldClose
 * @see eogllPollEvents
 *
 * This function swaps the buffers for the given window.
 * This function should be called every frame.
 *
 * This function is used to update the window's display.
 */
EOGLL_DECL_FUNC void eogllSwapBuffers(EogllWindow* window);

/**
 * @brief Destroys a window
 * @param window The window to destroy
 * @see eogllCreateWindow
 *
 * This function destroys the given window.
 * This function should be called when you are done with the window.
 */
EOGLL_DECL_FUNC void eogllDestroyWindow(EogllWindow* window);

#define DEPRECATED HEDLEY_DEPRECATED_FOR(0.2.6, window->press[key])
/**
 * @brief Gets if a key is pressed
 * @param window The window to check
 * @param key The key to check
 * @return Whether or not the key is pressed
 * @see eogllGetKeyRelease
 * @see eogllGetKeyIsDown
 *
 * @deprecated This function is deprecated (since 0.2.6), use window->press[key] instead
 *
 * This function checks if the given key is pressed.
 */
EOGLL_DECL_FUNC_ND DEPRECATED bool eogllGetKeyPress(EogllWindow* window, int key);
#undef DEPRECATED

#define DEPRECATED HEDLEY_DEPRECATED_FOR(0.2.6, window->release[key])
/**
 * @brief Gets if a key is released
 * @param window The window to check
 * @param key The key to check
 * @return Whether or not the key is released
 * @see eogllGetKeyPress
 * @see eogllGetKeyIsDown
 *
 * @deprecated This function is deprecated (since 0.2.6), use window->release[key] instead
 *
 * This function checks if the given key is released.
 */
EOGLL_DECL_FUNC_ND DEPRECATED bool eogllGetKeyRelease(EogllWindow* window, int key);
#undef DEPRECATED

#define DEPRECATED HEDLEY_DEPRECATED_FOR(0.2.6, window->isDown[key])
/**
 * @brief Gets if a key is down
 * @param window The window to check
 * @param key The key to check
 * @return Whether or not the key is down
 * @see eogllGetKeyPress
 * @see eogllGetKeyRelease
 *
 * @deprecated This function is deprecated (since 0.2.6), use window->isDown[key] instead
 *
 * This function checks if the given key is down.
 */
EOGLL_DECL_FUNC_ND DEPRECATED bool eogllGetKeyIsDown(EogllWindow* window, int key);
#undef DEPRECATED

#define DEPRECATED HEDLEY_DEPRECATED_FOR(0.2.6, window->mousePress[key])
/**
 * @brief Gets if a mouse button is pressed
 * @param window The window to check
 * @param button The mouse button to check
 * @return Whether or not the mouse button is pressed
 * @see eogllGetMouseRelease
 * @see eogllGetMouseIsDown
 *
 * @deprecated This function is deprecated (since 0.2.6), use window->mousePress[button] instead
 *
 * This function checks if the given mouse button is pressed.
 */
EOGLL_DECL_FUNC_ND DEPRECATED bool eogllGetMousePress(EogllWindow* window, int button);
#undef DEPRECATED

#define DEPRECATED HEDLEY_DEPRECATED_FOR(0.2.6, window->mouseRelease[key])
/**
 * @brief Gets if a mouse button is released
 * @param window The window to check
 * @param button The mouse button to check
 * @return Whether or not the mouse button is released
 * @see eogllGetMousePress
 * @see eogllGetMouseIsDown
 *
 * @deprecated This function is deprecated (since 0.2.6), use window->mouseRelease[button] instead
 *
 * This function checks if the given mouse button is released.
 */
EOGLL_DECL_FUNC_ND DEPRECATED bool eogllGetMouseRelease(EogllWindow* window, int button);
#undef DEPRECATED

#define DEPRECATED HEDLEY_DEPRECATED_FOR(0.2.6, window->mouseIsDown[key])
/**
 * @brief Gets if a mouse button is down
 * @param window The window to check
 * @param button The mouse button to check
 * @return Whether or not the mouse button is down
 * @see eogllGetMousePress
 * @see eogllGetMouseRelease
 *
 * @deprecated This function is deprecated (since 0.2.6), use window->mouseIsDown[button] instead
 *
 * This function checks if the given mouse button is down.
 */
EOGLL_DECL_FUNC_ND DEPRECATED bool eogllGetMouseIsDown(EogllWindow* window, int button);
#undef DEPRECATED

/**
 * @brief Gets the position of the mouse
 * @param window The window to get the mouse position for
 * @param xpos A pointer to the destination of the x position
 * @param ypos A pointer to the destination of the y position
 * @see eogllSetMousePos
 * @see EogllWindow
 *
 * This function gets the position of the mouse.
 * This function is effectively the same as using window->mousex and window->mousey.
 */
EOGLL_DECL_FUNC void eogllGetMousePos(EogllWindow* window, double* xpos, double* ypos);

/**
 * @brief Sets the position of the mouse
 * @param window The window to set the mouse position for
 * @param xpos The x position to set
 * @param ypos The y position to set
 * @see eogllGetMousePos
 * @see EogllWindow
 *
 * This function sets the position of the mouse.
 */
EOGLL_DECL_FUNC void eogllSetMousePos(EogllWindow* window, double xpos, double ypos);

/**
 * @brief Gets the delta of the mouse
 * @param window The window to get the mouse delta for
 * @param dxpos A pointer to the destination of the x delta
 * @param dypos A pointer to the destination of the y delta
 * @see EogllWindow
 *
 * This function gets the delta of the mouse.
 * This function is effectively the same as using window->mousedx and window->mousedy.
 */
EOGLL_DECL_FUNC void eogllGetMouseDelta(EogllWindow* window, double* dxpos, double* dypos);

/**
 * @brief Gets the scroll of the mouse
 * @param window The window to get the mouse scroll for
 * @param xscroll A pointer to the destination of the x scroll
 * @param yscroll A pointer to the destination of the y scroll
 * @see EogllWindow
 *
 * This function gets the scroll of the mouse.
 * This function is effectively the same as using window->mouseScrollx and window->mouseScrolly.
 */
EOGLL_DECL_FUNC void eogllGetMouseScroll(EogllWindow* window, double* xscroll, double* yscroll);

/**
 * @brief Gets the size of the window
 * @param window The window to get the size for
 * @param width A pointer to the destination of the width
 * @param height A pointer to the destination of the height
 * @see eogllSetWindowSize
 * @see EogllWindow
 *
 * This function gets the size of the window.
 * This function is effectively the same as using window->width and window->height.
 */
EOGLL_DECL_FUNC void eogllGetWindowSize(EogllWindow* window, uint32_t* width, uint32_t* height);

/**
 * @brief Sets the size of the window
 * @param window The window to set the size for
 * @param width The width to set
 * @param height The height to set
 * @see eogllGetWindowSize
 * @see EogllWindow
 *
 * This function sets the size of the window.
 */
EOGLL_DECL_FUNC void eogllSetWindowSize(EogllWindow* window, uint32_t width, uint32_t height);

/**
 * @brief Gets the position of the window
 * @param window The window to get the position for
 * @param x A pointer to the destination of the x position
 * @param y A pointer to the destination of the y position
 * @see eogllSetWindowPos
 * @see EogllWindow
 *
 * This function gets the position of the window.
 */
EOGLL_DECL_FUNC void eogllGetWindowPos(EogllWindow* window, int* x, int* y);

/**
 * @brief Sets the position of the window
 * @param window The window to set the position for
 * @param x The x position to set
 * @param y The y position to set
 * @see eogllGetWindowPos
 * @see EogllWindow
 *
 * This function sets the position of the window.
 */
EOGLL_DECL_FUNC void eogllSetWindowPos(EogllWindow* window, int x, int y);

/**
 * @brief Gets the current cursor pos
 * @param window The window to get the cursor pos for
 * @param xpos A pointer to the destination of the x position
 * @param ypos A pointer to the destination of the y position
 * @see eogllSetCursorPos
 * @see EogllWindow
 *
 * This function gets the current cursor pos.
 * This function is different from eogllGetMousePos:
 * eogllGetMousePos is updated by a callback function, so it's updated whenever the mouse moves, but eogllGetCursorPos gets the current cursor pos, so it's only updated when you call this function.
 * eogllGetCursorPos is more CPU intensive than eogllGetMousePos, so you should only use it when you need to.
 */
EOGLL_DECL_FUNC void eogllGetCursorPos(EogllWindow* window, double* xpos, double* ypos);

/**
 * @brief Sets the cursor pos
 * @param window The window to set the cursor pos for
 * @param xpos The x position to set
 * @param ypos The y position to set
 * @see eogllGetCursorPos
 * @see EogllWindow
 *
 * This function sets the cursor pos.
 * This function is identical to eogllSetMousePos.
 */
EOGLL_DECL_FUNC void eogllSetCursorPos(EogllWindow* window, double xpos, double ypos);

/**
 * @brief Centers the window on the current monitor
 * @param window The window to center
 * @see EogllWindow
 *
 * This function centers the window on the current monitor.
 * Very useful when creating a splash screen (undecorated) window.
 */
EOGLL_DECL_FUNC void eogllCenterWindow(EogllWindow* window);

/**
 * @brief Sets the cursor mode
 * @param window The window to set the cursor mode for
 * @param mode The cursor mode to set
 * @see EogllWindow
 * @see EOGLL_CURSOR_NORMAL
 * @see EOGLL_CURSOR_HIDDEN
 * @see EOGLL_CURSOR_DISABLED
 *
 * This function sets the cursor mode.
 * This function is effectively the same as using glfwSetInputMode(window->window, GLFW_CURSOR, mode).
 */
EOGLL_DECL_FUNC void eogllSetCursorMode(EogllWindow* window, int mode);

#ifdef __cplusplus
}
#endif

#endif //_EOGLL_WINDOW_H_
