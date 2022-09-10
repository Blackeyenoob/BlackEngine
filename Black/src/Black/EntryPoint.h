 #pragma once

#ifdef BK_PLATFORM_WINDOWS

extern Black::Application* Black::CreateApplication();

int main(int argc, char** argv) {
	BK_INIT;
	BK_CORE_WARN("Initialized Log..........");
	BK_WARN("Initialized System.........");
	int a = 89;

	BK_INFO("Hello! Var={0}", a);
	auto app = Black::CreateApplication();
	app->Run();
	delete app;
}
#endif // BK_PLATFORM_WINDOWS

