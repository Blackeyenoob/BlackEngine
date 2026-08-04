#pragma once

#include "Black/Core.h"
#include "Black/Renderer/RenderCommand.h"
#include "Black/Renderer/Shader.h"
#include "Black/Renderer/VertexArray.h"

namespace Black {

	class BLACK_API Renderer
	{
	public:
		static void Init();
		static void Shutdown();

		static void BeginScene();
		static void EndScene();

		static void Submit(const Ref<Shader>& shader, const Ref<VertexArray>& vertexArray, uint32_t indexCount = 0);

		inline static RendererAPI::API GetAPI() { return RendererAPI::GetAPI(); }
	};

}
