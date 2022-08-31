 #pragma once

#ifdef BK_PLATFORM_WINDOWS

extern Black::Application* Black::CreateApplication();

int main(int argc,char** argv) {
	
	printf("Start\n");
	auto app = Black::CreateApplication();
	app->Run();
	delete app;
}

#endif // BK_PLATFORM_WINDOWS

