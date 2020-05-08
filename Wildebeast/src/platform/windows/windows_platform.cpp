#include "wbpch.h"
#include "platform/windows/windows_platform.h"
#include "platform/windows/windows_window.h"
#include "platform/windows/events/windows_scancodes.h"
#include <xinput.h>

namespace wb {
    bool WindowsPlatform::_wbGamepadConnected = false;

    u32 WindowsScancodeToWBScanCode(LPARAM lParam, WPARAM wParam) {
        u32 code;
        int nScanCode = (lParam >> 16) & 0xFF;

        if (nScanCode == 0) {
            switch (wParam) {
            case VK_CLEAR: return WB_KEYCODE_CLEAR;
            case VK_MODECHANGE: return WB_KEYCODE_MODE;
            case VK_SELECT: return WB_KEYCODE_SELECT;
            case VK_EXECUTE: return WB_KEYCODE_EXECUTE;
            case VK_HELP: return WB_KEYCODE_HELP;

            case VK_F13: return WB_KEYCODE_F13;
            case VK_F14: return WB_KEYCODE_F14;
            case VK_F15: return WB_KEYCODE_F15;
            case VK_F16: return WB_KEYCODE_F16;
            case VK_F17: return WB_KEYCODE_F17;
            case VK_F18: return WB_KEYCODE_F18;
            case VK_F19: return WB_KEYCODE_F19;
            case VK_F20: return WB_KEYCODE_F20;
            case VK_F21: return WB_KEYCODE_F21;
            case VK_F22: return WB_KEYCODE_F22;
            case VK_F23: return WB_KEYCODE_F23;
            case VK_F24: return WB_KEYCODE_F24;

            case VK_OEM_NEC_EQUAL: return WB_KEYCODE_KP_EQUALS;
            case VK_BROWSER_BACK: return WB_KEYCODE_AC_BACK;
            case VK_BROWSER_FORWARD: return WB_KEYCODE_AC_FORWARD;
            case VK_BROWSER_REFRESH: return WB_KEYCODE_AC_REFRESH;
            case VK_BROWSER_STOP: return WB_KEYCODE_AC_STOP;
            case VK_BROWSER_SEARCH: return WB_KEYCODE_AC_SEARCH;
            case VK_BROWSER_FAVORITES: return WB_KEYCODE_AC_BOOKMARKS;
            case VK_BROWSER_HOME: return WB_KEYCODE_AC_HOME;
            case VK_VOLUME_MUTE: return WB_KEYCODE_AUDIOMUTE;
            case VK_VOLUME_DOWN: return WB_KEYCODE_VOLUMEDOWN;
            case VK_VOLUME_UP: return WB_KEYCODE_VOLUMEUP;

            case VK_MEDIA_NEXT_TRACK: return WB_KEYCODE_AUDIONEXT;
            case VK_MEDIA_PREV_TRACK: return WB_KEYCODE_AUDIOPREV;
            case VK_MEDIA_STOP: return WB_KEYCODE_AUDIOSTOP;
            case VK_MEDIA_PLAY_PAUSE: return WB_KEYCODE_AUDIOPLAY;
            case VK_LAUNCH_MAIL: return WB_KEYCODE_MAIL;
            case VK_LAUNCH_MEDIA_SELECT: return WB_KEYCODE_MEDIASELECT;

            case VK_OEM_102: return WB_KEYCODE_NONUSBACKSLASH;

            case VK_ATTN: return WB_KEYCODE_SYSREQ;
            case VK_CRSEL: return WB_KEYCODE_CRSEL;
            case VK_EXSEL: return WB_KEYCODE_EXSEL;
            case VK_OEM_CLEAR: return WB_KEYCODE_CLEAR;

            case VK_LAUNCH_APP1: return WB_KEYCODE_APP1;
            case VK_LAUNCH_APP2: return WB_KEYCODE_APP2;

            default: return WB_KEYCODE_UNKNOWN;
            }
        }

        if (nScanCode > 127) {
            return WB_KEYCODE_UNKNOWN;
        }

        code = windows_scancode_table[nScanCode];

        char bIsExtended = (lParam & (1 << 24)) != 0;

        if (bIsExtended) {
            switch (code) {
            case WB_KEYCODE_HOME:
                return WB_KEYCODE_KP_7;
            case WB_KEYCODE_UP:
                return WB_KEYCODE_KP_8;
            case WB_KEYCODE_PAGEUP:
                return WB_KEYCODE_KP_9;
            case WB_KEYCODE_LEFT:
                return WB_KEYCODE_KP_4;
            case WB_KEYCODE_RIGHT:
                return WB_KEYCODE_KP_6;
            case WB_KEYCODE_END:
                return WB_KEYCODE_KP_1;
            case WB_KEYCODE_DOWN:
                return WB_KEYCODE_KP_2;
            case WB_KEYCODE_PAGEDOWN:
                return WB_KEYCODE_KP_3;
            case WB_KEYCODE_INSERT:
                return WB_KEYCODE_KP_0;
            case WB_KEYCODE_DELETE:
                return WB_KEYCODE_KP_PERIOD;
            case WB_KEYCODE_PRINTSCREEN:
                return WB_KEYCODE_KP_MULTIPLY;
            default:
                break;
            }
        }
        else {
            switch (code)
            {
            case WB_KEYCODE_RETURN:
                return WB_KEYCODE_KP_ENTER;
            case WB_KEYCODE_LALT:
                return WB_KEYCODE_RALT;
            case WB_KEYCODE_LCTRL:
                return WB_KEYCODE_RCTRL;
            case WB_KEYCODE_SLASH:
                return WB_KEYCODE_KP_DIVIDE;
            case WB_KEYCODE_CAPSLOCK:
                return WB_KEYCODE_KP_PLUS;
            default:
                break;
            }
        }

        return code;
    }

    i16 normalizeL(i16 input) {
        if (abs(input) < XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE) {
            return 0;
        }
        else {
            return input;
        }
    }

    i16 normalizeR(i16 input) {
        if (abs(input) < XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE) {
            return 0;
        }
        else {
            return input;
        }
    }

    u8 normalizeT(u8 input) {
        if (abs(input) < XINPUT_GAMEPAD_TRIGGER_THRESHOLD) {
            return 0;
        }
        else {
            return input;
        }
    }

    LRESULT WindowsPlatform::HandleWin32Message(WindowsWindow* window, WinEventParams params) {
        Event event;

        // TODO(Chris): migrate handling windows-based items in WindowsWindow.
        // TODO(Chris): migrate many input events that don't require Window (e.g. keyboard) to the main OnUpdate loop

        switch (params.uMsg) {
        case WM_CLOSE:
        case WM_QUIT: {
            event.Type = WB_EVENT_QUIT;
        } break;
        case WM_SETFOCUS: {
            event.Type = WB_EVENT_WINDOW_EVENT;
            event.Window.Event = WB_WINDOWEVENT_FOCUSED;
        } break;
        case WM_KILLFOCUS: {
            event.Type = WB_EVENT_WINDOW_EVENT;
            event.Window.Event = WB_WINDOWEVENT_UNFOCUSED;
        } break;
        case WM_ACTIVATE: {
            event.Type = WB_EVENT_WINDOW_EVENT;
            event.Window.Event = WB_WINDOWEVENT_SHOWN;
        } break;
        case WM_LBUTTONUP:
        case WM_RBUTTONUP:
        case WM_MBUTTONUP:
        case WM_XBUTTONUP:
        case WM_LBUTTONDOWN:
        case WM_RBUTTONDOWN:
        case WM_MBUTTONDOWN:
        case WM_XBUTTONDOWN: {
            u8 button;
            u32 action;

            if (params.uMsg == WM_LBUTTONDOWN || params.uMsg == WM_LBUTTONUP)
                button = WB_MOUSEBUTTON_LEFT;
            else if (params.uMsg == WM_RBUTTONDOWN || params.uMsg == WM_RBUTTONUP)
                button = WB_MOUSEBUTTON_RIGHT;
            else if (params.uMsg == WM_MBUTTONDOWN || params.uMsg == WM_MBUTTONUP)
                button = WB_MOUSEBUTTON_MIDDLE;
            else if (GET_XBUTTON_WPARAM(params.wParam) == XBUTTON1)
                button = WB_MOUSEBUTTON_X1;
            else
                button = WB_MOUSEBUTTON_X2;

            if (params.uMsg == WM_LBUTTONDOWN || params.uMsg == WM_RBUTTONDOWN || params.uMsg == WM_MBUTTONDOWN || params.uMsg == WM_XBUTTONDOWN)
                action = WB_EVENT_MOUSE_PRESSED;
            else
                action = WB_EVENT_MOUSE_RELEASED;

            // TODO(Chris): handle the X and Y coords of click
            event.Type = action;
            event.Button.Code = button;
        } break;
        case WM_MOUSEMOVE: {
            const int x = LOWORD(params.lParam);
            const int y = HIWORD(params.lParam);

            event.Type = WB_EVENT_MOUSE_MOVED;
            event.Motion.X = x;
            event.Motion.Y = y;
        } break;
        case WM_MOUSEWHEEL: {
            i32 yDelta = (i32)((SHORT)HIWORD(params.wParam) / (double)WHEEL_DELTA);

            event.Type = WB_EVENT_MOUSE_SCROLLED;
            event.Scroll.X = 0;
            event.Scroll.Y = yDelta;
        } break;
        case WM_MOUSEHWHEEL: {
            i32 xDelta = (i32)((SHORT)HIWORD(params.wParam) / (double)WHEEL_DELTA);

            event.Type = WB_EVENT_MOUSE_SCROLLED;
            event.Scroll.X = xDelta;
            event.Scroll.Y = 0;
        } break;
        case WM_SYSKEYDOWN:
        case WM_KEYDOWN: {
            u32 scancode = WindowsScancodeToWBScanCode(params.lParam, params.wParam);
            event.Type = WB_EVENT_KEY_PRESSED;
            event.Key.Code = scancode;
        } break;
        case WM_SYSKEYUP:
        case WM_KEYUP: {
            u32 scancode = WindowsScancodeToWBScanCode(params.lParam, params.wParam);
            event.Type = WB_EVENT_KEY_RELEASED;
            event.Key.Code = scancode;
        } break;
        case WM_MOVE: {
            event.Type = WB_EVENT_WINDOW_EVENT;
            event.Window.Event = WB_WINDOWEVENT_MOVED;
        } break;
        case WM_SIZE: {
            i32 width, height;
            width = LOWORD(params.lParam);
            height = HIWORD(params.lParam);

            event.Type = WB_EVENT_WINDOW_EVENT;
            event.Window.Event = WB_WINDOWEVENT_RESIZED;
            event.Window.Width = width;
            event.Window.Height = height;

            if (params.wParam == SIZE_MINIMIZED) {
                eventCallback(event);
                event = Event{};
                event.Type = WB_EVENT_WINDOW_EVENT;
                event.Window.Event = WB_WINDOWEVENT_MINIMIZED;
            }
            else if (params.wParam == SIZE_MAXIMIZED) {
                eventCallback(event);
                event = Event{};
                event.Type = WB_EVENT_WINDOW_EVENT;
                event.Window.Event = WB_WINDOWEVENT_MAXIMIZED;
            }
        } break;
        default:
            event.Type = WB_EVENT_NONE;
        }
        if (event.Type != WB_EVENT_NONE) {
            eventCallback(event);
        }

        return DefWindowProcW(params.hWnd, params.uMsg, params.wParam, params.lParam);
    }

    WindowsPlatform::WindowsPlatform() {

    }

    WindowsPlatform::~WindowsPlatform() {

    }

    void WindowsPlatform::Init() {
        
    }

    void WindowsPlatform::OnUpdate() {
        // TODO(Chris): Move this into proper functions
        XINPUT_STATE state;
        ZeroMemory(&state, sizeof(XINPUT_STATE));

        if (XInputGetState(0, &state) == ERROR_SUCCESS)
        {
            if (!_wbGamepadConnected) {
                _wbGamepadConnected = true;
                Event event;
                event.Type = WB_EVENT_GAMEPAD_CONNECTED;

                eventCallback(event);
            }


            // update state
            Event event;
            event.Type = WB_EVENT_GAMEPAD_STATE;

            event.Gamepad.LX = normalizeL(state.Gamepad.sThumbLX);
            event.Gamepad.LY = normalizeL(state.Gamepad.sThumbLY);
            event.Gamepad.RX = normalizeR(state.Gamepad.sThumbRX);
            event.Gamepad.RY = normalizeR(state.Gamepad.sThumbRY);
            event.Gamepad.LT = normalizeT(state.Gamepad.bLeftTrigger);
            event.Gamepad.RT = normalizeT(state.Gamepad.bRightTrigger);

            u8 dpad = 0;

            if (state.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_DOWN) {
                dpad |= WB_GAMEPAD_DOWN;
            }
            if (state.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_LEFT) {
                dpad |= WB_GAMEPAD_LEFT;
            }
            if (state.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_RIGHT) {
                dpad |= WB_GAMEPAD_RIGHT;
            }
            if (state.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_UP) {
                dpad |= WB_GAMEPAD_UP;
            }

            event.Gamepad.DPAD = dpad;

            u8 fpad = 0;

            if (state.Gamepad.wButtons & XINPUT_GAMEPAD_A) {
                fpad |= WB_GAMEPAD_A;
            }
            if (state.Gamepad.wButtons & XINPUT_GAMEPAD_X) {
                fpad |= WB_GAMEPAD_X;
            }
            if (state.Gamepad.wButtons & XINPUT_GAMEPAD_B) {
                fpad |= WB_GAMEPAD_B;
            }
            if (state.Gamepad.wButtons & XINPUT_GAMEPAD_Y) {
                fpad |= WB_GAMEPAD_Y;
            }

            event.Gamepad.FPAD = fpad;

            u8 aux = 0;

            if (state.Gamepad.wButtons & XINPUT_GAMEPAD_LEFT_SHOULDER) {
                aux |= WB_GAMEPAD_LB;
            }
            if (state.Gamepad.wButtons & XINPUT_GAMEPAD_RIGHT_SHOULDER) {
                aux |= WB_GAMEPAD_RB;
            }
            if (state.Gamepad.wButtons & XINPUT_GAMEPAD_LEFT_THUMB) {
                aux |= WB_GAMEPAD_LS;
            }
            if (state.Gamepad.wButtons & XINPUT_GAMEPAD_RIGHT_THUMB) {
                aux |= WB_GAMEPAD_RS;
            }
            if (state.Gamepad.wButtons & XINPUT_GAMEPAD_START) {
                aux |= WB_GAMEPAD_START;
            }
            if (state.Gamepad.wButtons & XINPUT_GAMEPAD_BACK) {
                aux |= WB_GAMEPAD_BACK;
            }

            event.Gamepad.AuxButtons = aux;

            eventCallback(event);
        }
        else {
            if (_wbGamepadConnected) {
                _wbGamepadConnected = false;
                Event event;
                event.Type = WB_EVENT_GAMEPAD_DISCONNECTED;

                eventCallback(event);
            }
        }

        MSG msg;

        while (PeekMessageW(&msg, NULL, 0, 0, PM_REMOVE)) {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
    }

    Window* WindowsPlatform::NewWindow(const WindowCtx& ctx) {
        return new WindowsWindow(this, ctx);
    }
}