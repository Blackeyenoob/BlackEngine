#include "bkpch.h"
#include "Black/Core/Window.h"

#ifdef BK_PLATFORM_WINDOWS
	#include "Platform/Windows/WindowsWindow.h"
#endif

namespace Black
{
	Scope<Window> Window::Create(const WindowProps& props)
	{
	#ifdef BK_PLATFORM_WINDOWS
		return CreateScope<WindowsWindow>(props);
	#else
		BK_CORE_ASSERT(false, "Unknown platform!");
		return nullptr;
	#endif
	}

}