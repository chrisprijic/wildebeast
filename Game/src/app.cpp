#include <wildebeast.h>

void onKeyPressed(wb::Event& e) {
	WB_TRACE("key pressed: {}", e.Key.Code);
}

void onKeyReleased(wb::Event& e) {
	WB_TRACE("key released: {}", e.Key.Code);
}

void onMousePressed(wb::Event& e) {
	WB_TRACE("mouse button pressed: {}", e.Button.Code);
}

void onMouseReleased(wb::Event& e) {
	WB_TRACE("mouse button released: {}", e.Button.Code);
}

void onMouseScrolled(wb::Event& e) {
	WB_TRACE("mouse scrolled: ({}, {})", e.Scroll.X, e.Scroll.Y);
}

void onMouseMoved(wb::Event& e) {
	WB_TRACE("mouse moved: ({}, {})", e.Motion.X, e.Motion.Y);
}

class SandboxApp : public wb::Application {
public:
	SandboxApp() {
	}

	~SandboxApp() {

	}

	void OnEvent(wb::Event& e) {
		wb::EventRouter router(e);

		router.ProcessEvent<wb::WB_EVENT_KEY_PRESSED>(onKeyPressed);
		router.ProcessEvent<wb::WB_EVENT_KEY_RELEASED>(onKeyReleased);
		router.ProcessEvent<wb::WB_EVENT_MOUSE_PRESSED>(onMousePressed);
		router.ProcessEvent<wb::WB_EVENT_MOUSE_RELEASED>(onMouseReleased);
		router.ProcessEvent<wb::WB_EVENT_MOUSE_SCROLLED>(onMouseScrolled);
		router.ProcessEvent<wb::WB_EVENT_MOUSE_MOVED>(onMouseMoved);
	}
};

void main() {
	wb::Log::Init();
	WB_INFO("Application Starting...");

	SandboxApp* app = new SandboxApp();

	app->Run();
	WB_INFO("Application Complete...");
}