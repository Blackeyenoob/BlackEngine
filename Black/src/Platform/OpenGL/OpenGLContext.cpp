#include "bkpch.h"
#include "Platform/OpenGL/OpenGLContext.h"

#include <GLFW/glfw3.h>
#include <glad/glad.h>

namespace Black {

	OpenGLContext::OpenGLContext(GLFWwindow* windowHandle)
		: m_WindowHandle(windowHandle)
	{
		BK_CORE_ASSERT(windowHandle, "Window handle is null!")
	}

	void OpenGLContext::Init()
	{
		BK_PROFILE_FUNCTION();

		glfwMakeContextCurrent(m_WindowHandle);
		int status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
		BK_CORE_ASSERT(status, "Failed to initialize Glad!");

		BK_CORE_INFO("OpenGL Info:");
		BK_CORE_INFO("  Vendor: {0}", (const char*)glGetString(GL_VENDOR));
		BK_CORE_INFO("  Renderer: {0}", (const char*)glGetString(GL_RENDERER));
		BK_CORE_INFO("  Version: {0}", (const char*)glGetString(GL_VERSION));

		BK_CORE_ASSERT(GLVersion.major > 4 || (GLVersion.major == 4 && GLVersion.minor >= 5), "Black requires at least OpenGL version 4.5!");
	}

	void OpenGLContext::SwapBuffers()
	{
		BK_PROFILE_FUNCTION();

		glfwSwapBuffers(m_WindowHandle);
	}

}
