#include <wildebeast.h>

class SandboxApp : public wb::Application {
public:
	SandboxApp() {
	}

	~SandboxApp() {

	}
};

void main() {
	wb::Log::Init();
	WB_INFO("Application Starting...");

	SandboxApp* app = new SandboxApp();

	app->run();
	WB_INFO("Application Complete...");
}