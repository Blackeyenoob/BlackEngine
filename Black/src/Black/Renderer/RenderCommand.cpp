#include "bkpch.h"
#include "Black/Renderer/RenderCommand.h"

namespace Black {

	Scope<RendererAPI> RenderCommand::s_RendererAPI = RendererAPI::Create();

}