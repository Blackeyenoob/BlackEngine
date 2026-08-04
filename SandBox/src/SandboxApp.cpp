#include <Black.h>
#include "ExampleLayer.h"

class Sandbox : public Black::Application {
public:
	Sandbox() {
		PushLayer(new ExampleLayer());
	}
	~Sandbox() {
	}
};

Black::Application* Black::CreateApplication() {
	return new Sandbox();
}
