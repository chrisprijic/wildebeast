#include <wildebeast.h>

class SandboxApp : public wb::Application {
public:
	SandboxApp() {
	}

	~SandboxApp() {

	}

	void OnEvent(wb::Event& e) {
		switch (e.Type) {
		case wb::WB_EVENT_KEY_PRESSED: {
			WB_TRACE("key pressed: {}", e.Key.Code);
		} break;
		case wb::WB_EVENT_KEY_RELEASED: {
			WB_TRACE("key released: {}", e.Key.Code);
		} break;
		case wb::WB_EVENT_MOUSE_PRESSED: {
			WB_TRACE("mouse button pressed: {}", e.Button.Code);
		} break;
		case wb::WB_EVENT_MOUSE_RELEASED: {
			WB_TRACE("mouse button released: {}", e.Button.Code);
		} break;
		case wb::WB_EVENT_MOUSE_SCROLLED: {
			WB_TRACE("mouse scrolled: ({}, {})", e.Scroll.X, e.Scroll.Y);
		} break;
		case wb::WB_EVENT_MOUSE_MOVED: {
			WB_TRACE("mouse moved: ({}, {})", e.Motion.X, e.Motion.Y);
		} break;
		}
	}
};

void main() {
	wb::Log::Init();
	WB_INFO("Application Starting...");

	SandboxApp* app = new SandboxApp();

	app->Run();
	WB_INFO("Application Complete...");
}