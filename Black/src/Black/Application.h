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
	//����ͻ���
	Application* CreateApplication();
}

