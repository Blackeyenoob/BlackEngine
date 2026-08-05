#include <Black.h>
#include <Black/Core/EntryPoint.h>

#include "EditorLayer.h"

namespace Black {

	class Blacknut : public Application
	{
	public:
		Blacknut(const ApplicationSpecification& spec)
			: Application(spec)
		{
			PushLayer(new EditorLayer());
		}
	};

	Application* CreateApplication(ApplicationCommandLineArgs args)
	{
		ApplicationSpecification spec;
		spec.Name = "Blacknut";
		spec.CommandLineArgs = args;

		return new Blacknut(spec);
	}

}
