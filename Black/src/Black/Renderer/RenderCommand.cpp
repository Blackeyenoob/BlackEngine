#include "bkpch.h"
#include "Black/Renderer/RenderCommand.h"
#include "Black/Renderer/RendererAPI.h"

namespace Black {

	static Scope<RendererAPI> s_RendererAPI;

	void RenderCommand::Init()
	{
		s_RendererAPI = RendererAPI::Create();
		s_RendererAPI->Init();
	}

	void RenderCommand::SetViewport(uint32_t x, uint32_t y, uint32_t width, uint32_t height)
	{
		s_RendererAPI->SetViewport(x, y, width, height);
	}

	void RenderCommand::SetClearColor(const glm::vec4& color)
	{
		s_RendererAPI->SetClearColor(color);
	}

	void RenderCommand::Clear()
	{
		s_RendererAPI->Clear();
	}

	void RenderCommand::DrawIndexed(const Ref<VertexArray>& vertexArray, uint32_t indexCount)
	{
		s_RendererAPI->DrawIndexed(vertexArray, indexCount);
	}

}
