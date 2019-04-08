#include <wb.h>

class SandboxApp : public wb::Application {
public:
	SandboxApp() {

	}

	~SandboxApp() {

	}
};

void main() {
	SandboxApp* app = new SandboxApp();

	app->run();
}