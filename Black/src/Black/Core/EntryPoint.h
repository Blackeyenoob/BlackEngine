#pragma once
#include "Black/Core/Base.h"
#include "Black/Core/Application.h"

#ifdef BK_PLATFORM_WINDOWS

extern Black::Application* Black::CreateApplication(ApplicationCommandLineArgs args);

int main(int argc, char** argv)
{
	Black::Log::Init();

	BK_PROFILE_BEGIN_SESSION("Startup", "BlackProfile-Startup.json");
	auto app = Black::CreateApplication({ argc, argv });
	BK_PROFILE_END_SESSION();

	BK_PROFILE_BEGIN_SESSION("Runtime", "BlackProfile-Runtime.json");
	app->Run();
	BK_PROFILE_END_SESSION();

	BK_PROFILE_BEGIN_SESSION("Shutdown", "BlackProfile-Shutdown.json");
	delete app;
	BK_PROFILE_END_SESSION();
}

#endif
