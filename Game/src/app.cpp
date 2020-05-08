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

void onWindowEvent(wb::Event& e) {
	switch (e.Window.Event) {
	case wb::WB_WINDOWEVENT_RESIZED: {
		WB_TRACE("new window size: {}, {}", e.Window.Width, e.Window.Height);
	} break;
	case wb::WB_WINDOWEVENT_FOCUSED: {
		WB_TRACE("window focused");
	} break;
	case wb::WB_WINDOWEVENT_UNFOCUSED: {
		WB_TRACE("window unfocused");
	} break;
	case wb::WB_WINDOWEVENT_EXPOSED: {
		WB_TRACE("window exposed");
	} break;
	case wb::WB_WINDOWEVENT_MOVED: {
		WB_TRACE("window moved");
	} break;
	case wb::WB_WINDOWEVENT_MINIMIZED: {
		WB_TRACE("window minimized");
	} break;
	case wb::WB_WINDOWEVENT_MAXIMIZED: {
		WB_TRACE("window maximized");
	} break;
	// TODO(Chris): handle window/mouse interactions
	}
}

void onGamepad(wb::Event& event) {
	WB_TRACE("gamepad left: ({}, {})", event.Gamepad.LX, event.Gamepad.LY);
	WB_TRACE("gamepad right: ({}, {})", event.Gamepad.RX, event.Gamepad.RY);
	WB_TRACE("gamepad triggers: ({}, {})", event.Gamepad.LT, event.Gamepad.RT);
	if (event.Gamepad.DPAD & WB_GAMEPAD_DOWN)
		WB_TRACE("gamepad dpad down");
	if (event.Gamepad.DPAD & WB_GAMEPAD_LEFT)
		WB_TRACE("gamepad dpad left");
	if (event.Gamepad.DPAD & WB_GAMEPAD_RIGHT)
		WB_TRACE("gamepad dpad right");
	if (event.Gamepad.DPAD & WB_GAMEPAD_UP)
		WB_TRACE("gamepad dpad up");

	if (event.Gamepad.FPAD & WB_GAMEPAD_A)
		WB_TRACE("gamepad fpad A");
	if (event.Gamepad.FPAD & WB_GAMEPAD_X)
		WB_TRACE("gamepad fpad X");
	if (event.Gamepad.FPAD & WB_GAMEPAD_B)
		WB_TRACE("gamepad fpad B");
	if (event.Gamepad.FPAD & WB_GAMEPAD_Y)
		WB_TRACE("gamepad fpad Y");

	if (event.Gamepad.AuxButtons & WB_GAMEPAD_LB)
		WB_TRACE("gamepad left shoulder");
	if (event.Gamepad.AuxButtons & WB_GAMEPAD_RB)
		WB_TRACE("gamepad right shoulder");
	if (event.Gamepad.AuxButtons & WB_GAMEPAD_LS)
		WB_TRACE("gamepad left stick");
	if (event.Gamepad.AuxButtons & WB_GAMEPAD_RS)
		WB_TRACE("gamepad right stick");
	if (event.Gamepad.AuxButtons & WB_GAMEPAD_START)
		WB_TRACE("gamepad start");
	if (event.Gamepad.AuxButtons & WB_GAMEPAD_BACK)
		WB_TRACE("gamepad back");
}

void onGamepadConnect(wb::Event& event) {
	WB_TRACE("controller connected");
}

void onGamepadDisconnect(wb::Event& event) {
	WB_TRACE("controller disconnected");
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

		router.ProcessEvent<wb::WB_EVENT_WINDOW_EVENT>(onWindowEvent);

		router.ProcessEvent<wb::WB_EVENT_GAMEPAD_CONNECTED>(onGamepadConnect);
		router.ProcessEvent<wb::WB_EVENT_GAMEPAD_DISCONNECTED>(onGamepadDisconnect);
		router.ProcessEvent<wb::WB_EVENT_GAMEPAD_STATE>(onGamepad);
	}
};

void main() {
	wb::Log::Init();
	WB_INFO("Application Starting...");

	SandboxApp* app = new SandboxApp();

	app->Run();
	WB_INFO("Application Complete...");
}