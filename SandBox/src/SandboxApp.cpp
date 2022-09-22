#include <Black.h>
class Sandbox :public Black::Application {
public:
	Sandbox() {

	}
	~Sandbox() {

	}
};

Black::Application* Black::CreateApplication() {
	return new Sandbox();
}