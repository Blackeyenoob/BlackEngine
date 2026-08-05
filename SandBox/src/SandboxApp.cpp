#include <Black.h>
#include <Black/Core/EntryPoint.h>

#include "Sandbox2D.h"
#include "ExampleLayer.h"

class Sandbox : public Black::Application
{
public:
	Sandbox(const Black::ApplicationSpecification& specification)
		: Black::Application(specification)
	{
		// PushLayer(new ExampleLayer());
		PushLayer(new Sandbox2D());
	}

	~Sandbox()
	{
	}
};

Black::Application* Black::CreateApplication(Black::ApplicationCommandLineArgs args)
{
	ApplicationSpecification spec;
	spec.Name = "Sandbox";
	spec.WorkingDirectory = "../Blacknut";
	spec.CommandLineArgs = args;

	return new Sandbox(spec);
}
