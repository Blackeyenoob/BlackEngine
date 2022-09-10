#include "Application.h"

#include "Black/Events/ApplicationEvent.h"
#include "Black/Log.h"

namespace Black {
	Application::Application() {

	}
	Application::~Application() {

	}

	void Application::Run() {

		WindowResizeEvent e(1280, 720);
		if (e.IsInCategory(EventCategoryApplication)) {
			BK_TRACE(e);
		}
		if (e.IsInCategory(EventCategoryInput)) {
			BK_TRACE(e);
		}
		while (true);
	}
}
