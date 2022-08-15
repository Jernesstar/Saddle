#pragma once

namespace Saddle {

enum KeyCode {
    // From SDL_scancode.h

    // Letter keys
    A = 4,
    B = 5,
    C = 6,
    D = 7,
    E = 8,
    F = 9,
    G = 10,
    H = 11,
    I = 12,
    J = 13,
    K = 14,
    L = 15,
    M = 16,
    N = 17,
    O = 18,
    P = 19,
    Q = 20,
    R = 21,
    S = 22,
    T = 23,
    U = 24,
    V = 25,
    W = 26,
    X = 27,
    Y = 28,
    Z = 29,

    // Symbol keys
    MINUS = 45, /* - */
    EQUALS = 46, /* = */
    LEFTBRACKET = 47, /* [ */
    RIGHTBRACKET = 48, /* ] */
    BACKSLASH = 49, /* \ */ 
    SEMICOLON = 51, /* ; */
    APOSTROPHE = 52, /* ' */
    BACKTICK = 53, /* ` */
    COMMA = 54, /* , */
    PERIOD = 55, /* . */
    SLASH = 56, /* / */

    // Number keys
    N_1 = 30, /* 1 */
    N_2 = 31, /* 2 */
    N_3 = 32, /* 3 */
    N_4 = 33, /* 4 */
    N_5 = 34, /* 5 */
    N_6 = 35, /* 6 */
    N_7 = 36, /* 7 */
    N_8 = 37, /* 8 */
    N_9 = 38, /* 9 */
    N_0 = 39, /* 0 */

    // Function keys
    F1 = 58,
    F2 = 59,
    F3 = 60,
    F4 = 61,
    F5 = 62,
    F6 = 63,
    F7 = 64,
    F8 = 65,
    F9 = 66,
    F10 = 67,
    F11 = 68,
    F12 = 69,
    F13 = 104,
    F14 = 105,
    F15 = 106,
    F16 = 107,
    F17 = 108,
    F18 = 109,
    F19 = 110,
    F20 = 111,
    F21 = 112,
    F22 = 113,
    F23 = 114,
    F24 = 115,

    RETURN = 40,
    ESCAPE = 41,
    BACKSPACE = 42,
    TAB = 43,
    SPACE = 44,
    CAPSLOCK = 57,
    PRINTSCREEN = 70,
    SCROLLLOCK = 71,
    PAUSE = 72,
    INSERT = 73,
    HOME = 74,
    PAGEUP = 75,
    DELETE = 76,
    END = 77,
    PAGEDOWN = 78,
    NUMLOCK = 83,

    LEFT_CTRL = 224,
    RIGHT_CTRL = 228,
    LEFT_SHIFT = 225,
    RIGHT_SHIFT = 229,
    LEFT_ALT = 226, 
    RIGHT_ALT = 230,
    WINDOWS_KEY = 227, /* LGUI in SDL */
    
    MUTE = 127,
    VOLUMEUP = 128,
    VOLUMEDOWN = 129,

    // Directional keys
    RIGHT = 79,
    LEFT = 80,
    DOWN = 81,
    UP = 82,
    
    // Keypad
    KP_1 = 89,
    KP_2 = 90,
    KP_3 = 91,
    KP_4 = 92,
    KP_5 = 93,
    KP_6 = 94,
    KP_7 = 95,
    KP_8 = 96,
    KP_9 = 97,
    KP_0 = 98,
    KP_DIVIDE = 84,
    KP_MULTIPLY = 85,
    KP_MINUS = 86,
    KP_PLUS = 87,
    KP_ENTER = 88,
    KP_PERIOD = 99,
    KP_EQUALS = 103,
    KP_COMMA = 133,
};

}