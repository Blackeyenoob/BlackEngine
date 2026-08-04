 #pragma once

#ifdef BK_PLATFORM_WINDOWS

extern Black::Application* Black::CreateApplication();

int main(int argc, char** argv) {
	BK_INIT;
	BK_CORE_WARN("Initialized Log..........");
	BK_WARN("Initialized System.........");

	try {
		auto app = Black::CreateApplication();
		app->Run();
		delete app;
	}
	catch (const std::exception& e) {
		BK_CORE_ERROR("Fatal Error: {0}", e.what());
		BK_ERROR("Fatal Error: {0}", e.what());
	}
	catch (...) {
		BK_CORE_ERROR("Unknown fatal error!");
		BK_ERROR("Unknown fatal error!");
	}

	// Console pause so user can see output before window closes
	std::cout << "Press Enter to exit..." << std::endl;
	std::cin.get();
}
#endif // BK_PLATFORM_WINDOWS

