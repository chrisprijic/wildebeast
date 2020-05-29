#include "wbpch.h"
#include "wb/debug/editor.h"

#include "platform/opengl/imgui_impl_opengl3.h"

extern IMGUI_IMPL_API LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

namespace wb {
    Editor::Editor(Window* window) {
        this->window = window;
    }

    Editor::~Editor() {
        ImGui_ImplOpenGL3_Shutdown();
    }

    void Editor::Init() {
        ImGui::CreateContext();
        ImGui::StyleColorsDark();
        ImGuiIO& io = ImGui::GetIO();
        io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
        io.BackendFlags |= ImGuiBackendFlags_HasMouseCursors;
        io.BackendFlags |= ImGuiBackendFlags_HasSetMousePos;
        io.BackendPlatformName = "imgui_impl_win32";
        io.ImeWindowHandle = window->GetNativeWindow();

        io.KeyMap[ImGuiKey_Tab] = WB_KEYCODE_TAB;
        io.KeyMap[ImGuiKey_LeftArrow] = WB_KEYCODE_LEFT;
        io.KeyMap[ImGuiKey_RightArrow] = WB_KEYCODE_RIGHT;
        io.KeyMap[ImGuiKey_UpArrow] = WB_KEYCODE_UP;
        io.KeyMap[ImGuiKey_DownArrow] = WB_KEYCODE_DOWN;
        io.KeyMap[ImGuiKey_PageUp] = WB_KEYCODE_PAGEUP;
        io.KeyMap[ImGuiKey_PageDown] = WB_KEYCODE_PAGEDOWN;
        io.KeyMap[ImGuiKey_Home] = WB_KEYCODE_HOME;
        io.KeyMap[ImGuiKey_End] = WB_KEYCODE_END;
        io.KeyMap[ImGuiKey_Insert] = WB_KEYCODE_INSERT;
        io.KeyMap[ImGuiKey_Delete] = WB_KEYCODE_DELETE;
        io.KeyMap[ImGuiKey_Backspace] = WB_KEYCODE_BACKSPACE;
        io.KeyMap[ImGuiKey_Space] = WB_KEYCODE_SPACE;
        io.KeyMap[ImGuiKey_Enter] = WB_KEYCODE_RETURN;
        io.KeyMap[ImGuiKey_Escape] = WB_KEYCODE_ESCAPE;
        io.KeyMap[ImGuiKey_KeyPadEnter] = WB_KEYCODE_RETURN;
        io.KeyMap[ImGuiKey_A] = WB_KEYCODE_A;
        io.KeyMap[ImGuiKey_C] = WB_KEYCODE_C;
        io.KeyMap[ImGuiKey_V] = WB_KEYCODE_V;
        io.KeyMap[ImGuiKey_X] = WB_KEYCODE_X;
        io.KeyMap[ImGuiKey_Y] = WB_KEYCODE_Y;
        io.KeyMap[ImGuiKey_Z] = WB_KEYCODE_Z;

        ImGui_ImplOpenGL3_Init("#version 410");
    }

    void Editor::OnUpdate() {
        ImGui_ImplOpenGL3_NewFrame();
        
        ImGuiIO& io = ImGui::GetIO();
        io.DisplaySize = ImVec2(window->GetDrawWidth(), window->GetDrawHeight());

        ImGui::NewFrame();

        static bool show = true;
        ImGui::ShowDemoWindow(&show);

        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
    }

    bool Editor::OnEvent(Event& e) {
        ImGuiIO& io = ImGui::GetIO();
        
        switch (e.Type) {
            case WB_EVENT_MOUSE_PRESSED:
            {
                int button = 0;
                if (e.Button.Type == WB_MOUSEBUTTON_LEFT) { button = 0; }
                if (e.Button.Type == WB_MOUSEBUTTON_RIGHT) { button = 1; }
                if (e.Button.Type == WB_MOUSEBUTTON_MIDDLE ) { button = 2; }
                if (e.Button.Type == WB_MOUSEBUTTON_X1) { button = 3; }
                if (e.Button.Type == WB_MOUSEBUTTON_X2) { button = 4; }

                io.MouseDown[button] = true;
                return true;
            } break;
            case WB_EVENT_MOUSE_RELEASED: {
                int button = 0;
                if (e.Button.Type == WB_MOUSEBUTTON_LEFT) { button = 0; }
                if (e.Button.Type == WB_MOUSEBUTTON_RIGHT) { button = 1; }
                if (e.Button.Type == WB_MOUSEBUTTON_MIDDLE) { button = 2; }
                if (e.Button.Type == WB_MOUSEBUTTON_X1) { button = 3; }
                if (e.Button.Type == WB_MOUSEBUTTON_X2) { button = 4; }

                io.MouseDown[button] = false;
                return true;
            } break;
            case WB_EVENT_MOUSE_MOVED: {
                io.MousePos = ImVec2(e.Motion.X, e.Motion.Y);
                return true;
            } break;
            case WB_EVENT_KEY_PRESSED: {
                io.KeysDown[e.Key.Code] = 1;
            } break;
            case WB_EVENT_KEY_RELEASED: {
                io.KeysDown[e.Key.Code] = 0;
            } break;
            case WB_EVENT_TEXT_INPUT: {
                io.AddInputCharacterUTF16((unsigned short) (e.Text.Char));
            } break;
            case WB_EVENT_MOUSE_SCROLLED: {
                io.MouseWheel += e.Scroll.Y;
                io.MouseWheelH += e.Scroll.X;
            } break;
            default: {
                return false;
            }
        }
    }
}