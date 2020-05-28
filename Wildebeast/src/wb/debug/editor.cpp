#include "wbpch.h"
#include "wb/debug/editor.h"

#include "platform/windows/imgui_impl_win32.h"
#include "platform/opengl/imgui_impl_opengl3.h"

extern IMGUI_IMPL_API LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

namespace wb {
    Editor::Editor(Window* window) {
        this->window = window;
    }

    Editor::~Editor() {
        ImGui_ImplWin32_Shutdown();
        ImGui_ImplOpenGL3_Shutdown();
    }

    void Editor::Init() {
        ImGui::CreateContext();
        ImGui::StyleColorsDark();
        ImGuiIO& io = ImGui::GetIO(); (void) io;
        io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;

        ImGui_ImplWin32_Init(window->GetNativeWindow());
        ImGui_ImplOpenGL3_Init("#version 410");
    }

    void Editor::OnUpdate() {
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplWin32_NewFrame();
        ImGui::NewFrame();

        static bool show = true;
        ImGui::ShowDemoWindow(&show);

        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
    }

    void Editor::OnEvent(Event& e) {

    }
}