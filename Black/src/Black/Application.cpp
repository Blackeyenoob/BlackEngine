#include "bkpch.h"
#include "Application.h"

#include "Black/Events/ApplicationEvent.h"
#include "Black/Log.h"

namespace Black {
	Application::Application() {
		m_Window = std::unique_ptr<Window>(Window::Create());
	}
	Application::~Application() {

	}

	void Application::Run() {
		while (m_Running)
		{
			m_Window->OnUpdate();
		}
	}
}
