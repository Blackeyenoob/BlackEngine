#pragma once

#include "Core.h"

namespace Black {

	class BLACK_API Application
	{
	public:
		Application();
		virtual ~Application();

		void Run();
	};
	//定义客户端
	Application* CreateApplication();
}

