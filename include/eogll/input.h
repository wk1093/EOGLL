/**
 * @file input.h
 * @brief EOGLL input header file
 * @date 2024-01-28
 *
 * EOGLL input header file
 */

#pragma once
#ifndef _EOGLL_INPUT_H_
#define _EOGLL_INPUT_H_

#include "pch.h"

#ifdef __cplusplus
extern "C" {
#endif

#define EOGLL_KEY_UNKNOWN            -1

/* Printable keys */
#define EOGLL_KEY_SPACE              32
#define EOGLL_KEY_APOSTROPHE         39  /* ' */
#define EOGLL_KEY_COMMA              44  /* , */
#define EOGLL_KEY_MINUS              45  /* - */
#define EOGLL_KEY_PERIOD             46  /* . */
#define EOGLL_KEY_SLASH              47  /* / */
#define EOGLL_KEY_0                  48
#define EOGLL_KEY_1                  49
#define EOGLL_KEY_2                  50
#define EOGLL_KEY_3                  51
#define EOGLL_KEY_4                  52
#define EOGLL_KEY_5                  53
#define EOGLL_KEY_6                  54
#define EOGLL_KEY_7                  55
#define EOGLL_KEY_8                  56
#define EOGLL_KEY_9                  57
#define EOGLL_KEY_SEMICOLON          59  /* ; */
#define EOGLL_KEY_EQUAL              61  /* = */
#define EOGLL_KEY_A                  65
#define EOGLL_KEY_B                  66
#define EOGLL_KEY_C                  67
#define EOGLL_KEY_D                  68
#define EOGLL_KEY_E                  69
#define EOGLL_KEY_F                  70
#define EOGLL_KEY_G                  71
#define EOGLL_KEY_H                  72
#define EOGLL_KEY_I                  73
#define EOGLL_KEY_J                  74
#define EOGLL_KEY_K                  75
#define EOGLL_KEY_L                  76
#define EOGLL_KEY_M                  77
#define EOGLL_KEY_N                  78
#define EOGLL_KEY_O                  79
#define EOGLL_KEY_P                  80
#define EOGLL_KEY_Q                  81
#define EOGLL_KEY_R                  82
#define EOGLL_KEY_S                  83
#define EOGLL_KEY_T                  84
#define EOGLL_KEY_U                  85
#define EOGLL_KEY_V                  86
#define EOGLL_KEY_W                  87
#define EOGLL_KEY_X                  88
#define EOGLL_KEY_Y                  89
#define EOGLL_KEY_Z                  90
#define EOGLL_KEY_LEFT_BRACKET       91  /* [ */
#define EOGLL_KEY_BACKSLASH          92  /* \ */
#define EOGLL_KEY_RIGHT_BRACKET      93  /* ] */
#define EOGLL_KEY_GRAVE_ACCENT       96  /* ` */
#define EOGLL_KEY_WORLD_1            161 /* non-US #1 */
#define EOGLL_KEY_WORLD_2            162 /* non-US #2 */

/* Function keys */
#define EOGLL_KEY_ESCAPE             256
#define EOGLL_KEY_ENTER              257
#define EOGLL_KEY_TAB                258
#define EOGLL_KEY_BACKSPACE          259
#define EOGLL_KEY_INSERT             260
#define EOGLL_KEY_DELETE             261
#define EOGLL_KEY_RIGHT              262
#define EOGLL_KEY_LEFT               263
#define EOGLL_KEY_DOWN               264
#define EOGLL_KEY_UP                 265
#define EOGLL_KEY_PAGE_UP            266
#define EOGLL_KEY_PAGE_DOWN          267
#define EOGLL_KEY_HOME               268
#define EOGLL_KEY_END                269
#define EOGLL_KEY_CAPS_LOCK          280
#define EOGLL_KEY_SCROLL_LOCK        281
#define EOGLL_KEY_NUM_LOCK           282
#define EOGLL_KEY_PRINT_SCREEN       283
#define EOGLL_KEY_PAUSE              284
#define EOGLL_KEY_F1                 290
#define EOGLL_KEY_F2                 291
#define EOGLL_KEY_F3                 292
#define EOGLL_KEY_F4                 293
#define EOGLL_KEY_F5                 294
#define EOGLL_KEY_F6                 295
#define EOGLL_KEY_F7                 296
#define EOGLL_KEY_F8                 297
#define EOGLL_KEY_F9                 298
#define EOGLL_KEY_F10                299
#define EOGLL_KEY_F11                300
#define EOGLL_KEY_F12                301
#define EOGLL_KEY_F13                302
#define EOGLL_KEY_F14                303
#define EOGLL_KEY_F15                304
#define EOGLL_KEY_F16                305
#define EOGLL_KEY_F17                306
#define EOGLL_KEY_F18                307
#define EOGLL_KEY_F19                308
#define EOGLL_KEY_F20                309
#define EOGLL_KEY_F21                310
#define EOGLL_KEY_F22                311
#define EOGLL_KEY_F23                312
#define EOGLL_KEY_F24                313
#define EOGLL_KEY_F25                314
#define EOGLL_KEY_KP_0               320
#define EOGLL_KEY_KP_1               321
#define EOGLL_KEY_KP_2               322
#define EOGLL_KEY_KP_3               323
#define EOGLL_KEY_KP_4               324
#define EOGLL_KEY_KP_5               325
#define EOGLL_KEY_KP_6               326
#define EOGLL_KEY_KP_7               327
#define EOGLL_KEY_KP_8               328
#define EOGLL_KEY_KP_9               329
#define EOGLL_KEY_KP_DECIMAL         330
#define EOGLL_KEY_KP_DIVIDE          331
#define EOGLL_KEY_KP_MULTIPLY        332
#define EOGLL_KEY_KP_SUBTRACT        333
#define EOGLL_KEY_KP_ADD             334
#define EOGLL_KEY_KP_ENTER           335
#define EOGLL_KEY_KP_EQUAL           336
#define EOGLL_KEY_LEFT_SHIFT         340
#define EOGLL_KEY_LEFT_CONTROL       341
#define EOGLL_KEY_LEFT_ALT           342
#define EOGLL_KEY_LEFT_SUPER         343
#define EOGLL_KEY_RIGHT_SHIFT        344
#define EOGLL_KEY_RIGHT_CONTROL      345
#define EOGLL_KEY_RIGHT_ALT          346
#define EOGLL_KEY_RIGHT_SUPER        347
#define EOGLL_KEY_MENU               348

#define EOGLL_KEY_LAST               EOGLL_KEY_MENU


/* Mouse buttons */
#define EOGLL_MOUSE_BUTTON_1         0
#define EOGLL_MOUSE_BUTTON_2         1
#define EOGLL_MOUSE_BUTTON_3         2
#define EOGLL_MOUSE_BUTTON_4         3
#define EOGLL_MOUSE_BUTTON_5         4
#define EOGLL_MOUSE_BUTTON_6         5
#define EOGLL_MOUSE_BUTTON_7         6
#define EOGLL_MOUSE_BUTTON_8         7
#define EOGLL_MOUSE_BUTTON_LAST      EOGLL_MOUSE_BUTTON_8
#define EOGLL_MOUSE_BUTTON_LEFT      EOGLL_MOUSE_BUTTON_1
#define EOGLL_MOUSE_BUTTON_RIGHT     EOGLL_MOUSE_BUTTON_2
#define EOGLL_MOUSE_BUTTON_MIDDLE    EOGLL_MOUSE_BUTTON_3

#define EOGLL_RELEASE                0

#define EOGLL_PRESS                  1

/// Normal cursor mode
#define EOGLL_CURSOR_NORMAL          0x00034001

/// Hidden cursor mode
#define EOGLL_CURSOR_HIDDEN          0x00034002

/// Disabled cursor mode
#define EOGLL_CURSOR_DISABLED        0x00034003




#ifdef __cplusplus
}
#endif

#endif //_EOGLL_INPUT_H_
