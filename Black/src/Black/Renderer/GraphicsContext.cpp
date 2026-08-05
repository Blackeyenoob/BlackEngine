#include "bkpch.h"
#include "Black/Renderer/GraphicsContext.h"

#include "Black/Renderer/Renderer.h"
#include "Platform/OpenGL/OpenGLContext.h"

namespace Black {

	Scope<GraphicsContext> GraphicsContext::Create(void* window)
	{
		switch (Renderer::GetAPI())
		{
			case RendererAPI::API::None:    BK_CORE_ASSERT(false, "RendererAPI::None is currently not supported!"); return nullptr;
			case RendererAPI::API::OpenGL:  return CreateScope<OpenGLContext>(static_cast<GLFWwindow*>(window));
		}

		BK_CORE_ASSERT(false, "Unknown RendererAPI!");
		return nullptr;
	}

}