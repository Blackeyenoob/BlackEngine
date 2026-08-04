#include "bkpch.h"
#include "Black/Renderer/Renderer.h"
#include "Black/Renderer/RenderCommand.h"

namespace Black {

	void Renderer::Init()
	{
		RenderCommand::Init();
	}

	void Renderer::Shutdown()
	{
	}

	void Renderer::BeginScene()
	{
	}

	void Renderer::EndScene()
	{
	}

	void Renderer::Submit(const Ref<Shader>& shader, const Ref<VertexArray>& vertexArray, uint32_t indexCount)
	{
		shader->Bind();
		vertexArray->Bind();
		RenderCommand::DrawIndexed(vertexArray, indexCount);
	}

}
