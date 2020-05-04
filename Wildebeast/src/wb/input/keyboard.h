#pragma once

#include <iostream>

namespace wb {
    /**
     *  !!! defined from SDL_scancode.h
     *
     *  \brief The SDL keyboard scancode representation.
     *  
     *  Values of this type are used to represent keyboard keys, among other places
     *  in the \link SDL_Keysym::scancode key.keysym.scancode \endlink field of the
     *  SDL_Event structure.
     *  
     *  The values in this enumeration are based on the USB usage page standard:
     *  http://www.usb.org/developers/devclass_docs/Hut1_12v2.pdf
     */
    typedef enum WB_KEYCODE {
        WB_KEYCODE_UNKNOWN = 0,

        /** 
         *  \name Usage page 0x07
         *  
         *  These values are from usage page 0x07 (USB keyboard page).
         */
        /*@{*/

        WB_KEYCODE_A = 4,
        WB_KEYCODE_B = 5,
        WB_KEYCODE_C = 6,
        WB_KEYCODE_D = 7,
        WB_KEYCODE_E = 8,
        WB_KEYCODE_F = 9,
        WB_KEYCODE_G = 10,
        WB_KEYCODE_H = 11,
        WB_KEYCODE_I = 12,
        WB_KEYCODE_J = 13,
        WB_KEYCODE_K = 14,
        WB_KEYCODE_L = 15,
        WB_KEYCODE_M = 16,
        WB_KEYCODE_N = 17,
        WB_KEYCODE_O = 18,
        WB_KEYCODE_P = 19,
        WB_KEYCODE_Q = 20,
        WB_KEYCODE_R = 21,
        WB_KEYCODE_S = 22,
        WB_KEYCODE_T = 23,
        WB_KEYCODE_U = 24,
        WB_KEYCODE_V = 25,
        WB_KEYCODE_W = 26,
        WB_KEYCODE_X = 27,
        WB_KEYCODE_Y = 28,
        WB_KEYCODE_Z = 29,

        WB_KEYCODE_1 = 30,
        WB_KEYCODE_2 = 31,
        WB_KEYCODE_3 = 32,
        WB_KEYCODE_4 = 33,
        WB_KEYCODE_5 = 34,
        WB_KEYCODE_6 = 35,
        WB_KEYCODE_7 = 36,
        WB_KEYCODE_8 = 37,
        WB_KEYCODE_9 = 38,
        WB_KEYCODE_0 = 39,

        WB_KEYCODE_RETURN = 40,
        WB_KEYCODE_ESCAPE = 41,
        WB_KEYCODE_BACKSPACE = 42,
        WB_KEYCODE_TAB = 43,
        WB_KEYCODE_SPACE = 44,

        WB_KEYCODE_MINUS = 45,
        WB_KEYCODE_EQUALS = 46,
        WB_KEYCODE_LEFTBRACKET = 47,
        WB_KEYCODE_RIGHTBRACKET = 48,
        WB_KEYCODE_BACKSLASH = 49, /**< Located at the lower left of the return 
                                      *   key on ISO keyboards and at the right end 
                                      *   of the QWERTY row on ANSI keyboards. 
                                      *   Produces REVERSE SOLIDUS (backslash) and 
                                      *   VERTICAL LINE in a US layout, REVERSE 
                                      *   SOLIDUS and VERTICAL LINE in a UK Mac 
                                      *   layout, NUMBER SIGN and TILDE in a UK 
                                      *   Windows layout, DOLLAR SIGN and POUND SIGN
                                      *   in a Swiss German layout, NUMBER SIGN and 
                                      *   APOSTROPHE in a German layout, GRAVE 
                                      *   ACCENT and POUND SIGN in a French Mac 
                                      *   layout, and ASTERISK and MICRO SIGN in a 
                                      *   French Windows layout.
                                      */
        WB_KEYCODE_NONUSHASH = 50, /**< ISO USB keyboards actually use this code 
                                      *   instead of 49 for the same key, but all 
                                      *   OSes I've seen treat the two codes 
                                      *   identically. So, as an implementor, unless
                                      *   your keyboard generates both of those 
                                      *   codes and your OS treats them differently,
                                      *   you should generate WB_KEYCODE_BACKSLASH
                                      *   instead of this code. As a user, you 
                                      *   should not rely on this code because SDL 
                                      *   will never generate it with most (all?) 
                                      *   keyboards. 
                                      */
        WB_KEYCODE_SEMICOLON = 51,
        WB_KEYCODE_APOSTROPHE = 52,
        WB_KEYCODE_GRAVE = 53, /**< Located in the top left corner (on both ANSI 
                                  *   and ISO keyboards). Produces GRAVE ACCENT and 
                                  *   TILDE in a US Windows layout and in US and UK 
                                  *   Mac layouts on ANSI keyboards, GRAVE ACCENT 
                                  *   and NOT SIGN in a UK Windows layout, SECTION 
                                  *   SIGN and PLUS-MINUS SIGN in US and UK Mac 
                                  *   layouts on ISO keyboards, SECTION SIGN and 
                                  *   DEGREE SIGN in a Swiss German layout (Mac: 
                                  *   only on ISO keyboards), CIRCUMFLEX ACCENT and 
                                  *   DEGREE SIGN in a German layout (Mac: only on 
                                  *   ISO keyboards), SUPERSCRIPT TWO and TILDE in a
                                  *   French Windows layout, COMMERCIAL AT and 
                                  *   NUMBER SIGN in a French Mac layout on ISO 
                                  *   keyboards, and LESS-THAN SIGN and GREATER-THAN
                                  *   SIGN in a Swiss German, German, or French Mac 
                                  *   layout on ANSI keyboards.
                                  */
        WB_KEYCODE_COMMA = 54,
        WB_KEYCODE_PERIOD = 55,
        WB_KEYCODE_SLASH = 56,

        WB_KEYCODE_CAPSLOCK = 57,

        WB_KEYCODE_F1 = 58,
        WB_KEYCODE_F2 = 59,
        WB_KEYCODE_F3 = 60,
        WB_KEYCODE_F4 = 61,
        WB_KEYCODE_F5 = 62,
        WB_KEYCODE_F6 = 63,
        WB_KEYCODE_F7 = 64,
        WB_KEYCODE_F8 = 65,
        WB_KEYCODE_F9 = 66,
        WB_KEYCODE_F10 = 67,
        WB_KEYCODE_F11 = 68,
        WB_KEYCODE_F12 = 69,

        WB_KEYCODE_PRINTSCREEN = 70,
        WB_KEYCODE_SCROLLLOCK = 71,
        WB_KEYCODE_PAUSE = 72,
        WB_KEYCODE_INSERT = 73, /**< insert on PC, help on some Mac keyboards (but
                                       does send code 73, not 117) */
        WB_KEYCODE_HOME = 74,
        WB_KEYCODE_PAGEUP = 75,
        WB_KEYCODE_DELETE = 76,
        WB_KEYCODE_END = 77,
        WB_KEYCODE_PAGEDOWN = 78,
        WB_KEYCODE_RIGHT = 79,
        WB_KEYCODE_LEFT = 80,
        WB_KEYCODE_DOWN = 81,
        WB_KEYCODE_UP = 82,

        WB_KEYCODE_NUMLOCKCLEAR = 83, /**< num lock on PC, clear on Mac keyboards 
                                         */
        WB_KEYCODE_KP_DIVIDE = 84,
        WB_KEYCODE_KP_MULTIPLY = 85,
        WB_KEYCODE_KP_MINUS = 86,
        WB_KEYCODE_KP_PLUS = 87,
        WB_KEYCODE_KP_ENTER = 88,
        WB_KEYCODE_KP_1 = 89,
        WB_KEYCODE_KP_2 = 90,
        WB_KEYCODE_KP_3 = 91,
        WB_KEYCODE_KP_4 = 92,
        WB_KEYCODE_KP_5 = 93,
        WB_KEYCODE_KP_6 = 94,
        WB_KEYCODE_KP_7 = 95,
        WB_KEYCODE_KP_8 = 96,
        WB_KEYCODE_KP_9 = 97,
        WB_KEYCODE_KP_0 = 98,
        WB_KEYCODE_KP_PERIOD = 99,

        WB_KEYCODE_NONUSBACKSLASH = 100, /**< This is the additional key that ISO 
                                            *   keyboards have over ANSI ones, 
                                            *   located between left shift and Y. 
                                            *   Produces GRAVE ACCENT and TILDE in a
                                            *   US or UK Mac layout, REVERSE SOLIDUS
                                            *   (backslash) and VERTICAL LINE in a 
                                            *   US or UK Windows layout, and 
                                            *   LESS-THAN SIGN and GREATER-THAN SIGN
                                            *   in a Swiss German, German, or French
                                            *   layout. */
        WB_KEYCODE_APPLICATION = 101, /**< windows contextual menu, compose */
        WB_KEYCODE_POWER = 102, /**< The USB document says this is a status flag, 
                                   *   not a physical key - but some Mac keyboards 
                                   *   do have a power key. */
        WB_KEYCODE_KP_EQUALS = 103,
        WB_KEYCODE_F13 = 104,
        WB_KEYCODE_F14 = 105,
        WB_KEYCODE_F15 = 106,
        WB_KEYCODE_F16 = 107,
        WB_KEYCODE_F17 = 108,
        WB_KEYCODE_F18 = 109,
        WB_KEYCODE_F19 = 110,
        WB_KEYCODE_F20 = 111,
        WB_KEYCODE_F21 = 112,
        WB_KEYCODE_F22 = 113,
        WB_KEYCODE_F23 = 114,
        WB_KEYCODE_F24 = 115,
        WB_KEYCODE_EXECUTE = 116,
        WB_KEYCODE_HELP = 117,
        WB_KEYCODE_MENU = 118,
        WB_KEYCODE_SELECT = 119,
        WB_KEYCODE_STOP = 120,
        WB_KEYCODE_AGAIN = 121,   /**< redo */
        WB_KEYCODE_UNDO = 122,
        WB_KEYCODE_CUT = 123,
        WB_KEYCODE_COPY = 124,
        WB_KEYCODE_PASTE = 125,
        WB_KEYCODE_FIND = 126,
        WB_KEYCODE_MUTE = 127,
        WB_KEYCODE_VOLUMEUP = 128,
        WB_KEYCODE_VOLUMEDOWN = 129,
    /* not sure whether there's a reason to enable these */
    /*     WB_KEYCODE_LOCKINGCAPSLOCK = 130,  */
    /*     WB_KEYCODE_LOCKINGNUMLOCK = 131, */
    /*     WB_KEYCODE_LOCKINGSCROLLLOCK = 132, */
        WB_KEYCODE_KP_COMMA = 133,
        WB_KEYCODE_KP_EQUALSAS400 = 134,

        WB_KEYCODE_INTERNATIONAL1 = 135, /**< used on Asian keyboards, see 
                                                footnotes in USB doc */
        WB_KEYCODE_INTERNATIONAL2 = 136,
        WB_KEYCODE_INTERNATIONAL3 = 137, /**< Yen */
        WB_KEYCODE_INTERNATIONAL4 = 138,
        WB_KEYCODE_INTERNATIONAL5 = 139,
        WB_KEYCODE_INTERNATIONAL6 = 140,
        WB_KEYCODE_INTERNATIONAL7 = 141,
        WB_KEYCODE_INTERNATIONAL8 = 142,
        WB_KEYCODE_INTERNATIONAL9 = 143,
        WB_KEYCODE_LANG1 = 144, /**< Hangul/English toggle */
        WB_KEYCODE_LANG2 = 145, /**< Hanja conversion */
        WB_KEYCODE_LANG3 = 146, /**< Katakana */
        WB_KEYCODE_LANG4 = 147, /**< Hiragana */
        WB_KEYCODE_LANG5 = 148, /**< Zenkaku/Hankaku */
        WB_KEYCODE_LANG6 = 149, /**< reserved */
        WB_KEYCODE_LANG7 = 150, /**< reserved */
        WB_KEYCODE_LANG8 = 151, /**< reserved */
        WB_KEYCODE_LANG9 = 152, /**< reserved */

        WB_KEYCODE_ALTERASE = 153, /**< Erase-Eaze */
        WB_KEYCODE_SYSREQ = 154,
        WB_KEYCODE_CANCEL = 155,
        WB_KEYCODE_CLEAR = 156,
        WB_KEYCODE_PRIOR = 157,
        WB_KEYCODE_RETURN2 = 158,
        WB_KEYCODE_SEPARATOR = 159,
        WB_KEYCODE_OUT = 160,
        WB_KEYCODE_OPER = 161,
        WB_KEYCODE_CLEARAGAIN = 162,
        WB_KEYCODE_CRSEL = 163,
        WB_KEYCODE_EXSEL = 164,

        WB_KEYCODE_KP_00 = 176,
        WB_KEYCODE_KP_000 = 177,
        WB_KEYCODE_THOUSANDSSEPARATOR = 178,
        WB_KEYCODE_DECIMALSEPARATOR = 179,
        WB_KEYCODE_CURRENCYUNIT = 180,
        WB_KEYCODE_CURRENCYSUBUNIT = 181,
        WB_KEYCODE_KP_LEFTPAREN = 182,
        WB_KEYCODE_KP_RIGHTPAREN = 183,
        WB_KEYCODE_KP_LEFTBRACE = 184,
        WB_KEYCODE_KP_RIGHTBRACE = 185,
        WB_KEYCODE_KP_TAB = 186,
        WB_KEYCODE_KP_BACKSPACE = 187,
        WB_KEYCODE_KP_A = 188,
        WB_KEYCODE_KP_B = 189,
        WB_KEYCODE_KP_C = 190,
        WB_KEYCODE_KP_D = 191,
        WB_KEYCODE_KP_E = 192,
        WB_KEYCODE_KP_F = 193,
        WB_KEYCODE_KP_XOR = 194,
        WB_KEYCODE_KP_POWER = 195,
        WB_KEYCODE_KP_PERCENT = 196,
        WB_KEYCODE_KP_LESS = 197,
        WB_KEYCODE_KP_GREATER = 198,
        WB_KEYCODE_KP_AMPERSAND = 199,
        WB_KEYCODE_KP_DBLAMPERSAND = 200,
        WB_KEYCODE_KP_VERTICALBAR = 201,
        WB_KEYCODE_KP_DBLVERTICALBAR = 202,
        WB_KEYCODE_KP_COLON = 203,
        WB_KEYCODE_KP_HASH = 204,
        WB_KEYCODE_KP_SPACE = 205,
        WB_KEYCODE_KP_AT = 206,
        WB_KEYCODE_KP_EXCLAM = 207,
        WB_KEYCODE_KP_MEMSTORE = 208,
        WB_KEYCODE_KP_MEMRECALL = 209,
        WB_KEYCODE_KP_MEMCLEAR = 210,
        WB_KEYCODE_KP_MEMADD = 211,
        WB_KEYCODE_KP_MEMSUBTRACT = 212,
        WB_KEYCODE_KP_MEMMULTIPLY = 213,
        WB_KEYCODE_KP_MEMDIVIDE = 214,
        WB_KEYCODE_KP_PLUSMINUS = 215,
        WB_KEYCODE_KP_CLEAR = 216,
        WB_KEYCODE_KP_CLEARENTRY = 217,
        WB_KEYCODE_KP_BINARY = 218,
        WB_KEYCODE_KP_OCTAL = 219,
        WB_KEYCODE_KP_DECIMAL = 220,
        WB_KEYCODE_KP_HEXADECIMAL = 221,

        WB_KEYCODE_LCTRL = 224,
        WB_KEYCODE_LSHIFT = 225,
        WB_KEYCODE_LALT = 226, /**< alt, option */
        WB_KEYCODE_LGUI = 227, /**< windows, command (apple), meta */
        WB_KEYCODE_RCTRL = 228,
        WB_KEYCODE_RSHIFT = 229,
        WB_KEYCODE_RALT = 230, /**< alt gr, option */
        WB_KEYCODE_RGUI = 231, /**< windows, command (apple), meta */

        WB_KEYCODE_MODE = 257,    /**< I'm not sure if this is really not covered 
                                     *   by any of the above, but since there's a 
                                     *   special KMOD_MODE for it I'm adding it here
                                     */
    
        /*@}*//*Usage page 0x07*/

        /**
         *  \name Usage page 0x0C
         *  
         *  These values are mapped from usage page 0x0C (USB consumer page).
         */
        /*@{*/

        WB_KEYCODE_AUDIONEXT = 258,
        WB_KEYCODE_AUDIOPREV = 259,
        WB_KEYCODE_AUDIOSTOP = 260,
        WB_KEYCODE_AUDIOPLAY = 261,
        WB_KEYCODE_AUDIOMUTE = 262,
        WB_KEYCODE_MEDIASELECT = 263,
        WB_KEYCODE_WWW = 264,
        WB_KEYCODE_MAIL = 265,
        WB_KEYCODE_CALCULATOR = 266,
        WB_KEYCODE_COMPUTER = 267,
        WB_KEYCODE_AC_SEARCH = 268,
        WB_KEYCODE_AC_HOME = 269,
        WB_KEYCODE_AC_BACK = 270,
        WB_KEYCODE_AC_FORWARD = 271,
        WB_KEYCODE_AC_STOP = 272,
        WB_KEYCODE_AC_REFRESH = 273,
        WB_KEYCODE_AC_BOOKMARKS = 274,
    
        /*@}*//*Usage page 0x0C*/

        /**
         *  \name Walther keys
         *  
         *  These are values that Christian Walther added (for mac keyboard?).
         */
        /*@{*/

        WB_KEYCODE_BRIGHTNESSDOWN = 275,
        WB_KEYCODE_BRIGHTNESSUP = 276,
        WB_KEYCODE_DISPLAYSWITCH = 277, /**< display mirroring/dual display 
                                               switch, video mode switch */
        WB_KEYCODE_KBDILLUMTOGGLE = 278,
        WB_KEYCODE_KBDILLUMDOWN = 279,
        WB_KEYCODE_KBDILLUMUP = 280,
        WB_KEYCODE_EJECT = 281,
        WB_KEYCODE_SLEEP = 282,
    
	    WB_KEYCODE_APP1 = 283,
	    WB_KEYCODE_APP2 = 284,

        /*@}*//*Walther keys*/

        /* Add any other keys here. */

        WB_TOTAL_KEYCODES = 512 /**< not a key, just marks the number of scancodes 
                                     for array bounds */
    } WB_KEYCODE;


    inline std::ostream& operator<<(std::ostream& os, WB_KEYCODE keycode) {
        os << static_cast<int32_t>(keycode);
        return os;
    }

    typedef enum WB_KEYMOD {
        WB_KEYMOD_NONE,
        WB_KEYMOD_LEFTSHIFT,
        WB_KEYMOD_RIGHTSHIFT,
        WB_KEYMOD_LEFTCONTROL,
        WB_KEYMOD_RIGHTCONTROL,
        WB_KEYMOD_LEFTALT,
        WB_KEYMOD_RIGHTALT,
        WB_KEYMOD_NUMLOCK,
        WB_KEYMOD_CAPSLOCK,
        WB_KEYMOD_SCROLLLOCK,

        WB_TOTAL_KEYMODS
    } WB_KEYMOD;

    inline std::ostream& operator<<(std::ostream& os, WB_KEYMOD keymod) {
        os << static_cast<int32_t>(keymod);
        return os;
    }
}