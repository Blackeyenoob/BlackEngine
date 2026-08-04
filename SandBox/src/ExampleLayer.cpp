#include "ExampleLayer.h"
#include "Black/Renderer/Buffer.h"
#include "Black/Renderer/RenderCommand.h"
#include "Black/Renderer/Renderer.h"
#include "Black/Renderer/Shader.h"
#include "Black/Renderer/VertexArray.h"

ExampleLayer::ExampleLayer()
	: Layer("Example"), m_Camera(-1.6f, 1.6f, -0.9f, 0.9f)
{
}

void ExampleLayer::OnAttach()
{
	// Triangle
	float vertices[3 * 7] = {
		-0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 1.0f, 1.0f,
		 0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f,
		 0.0f,  0.5f, 0.0f, 1.0f, 1.0f, 0.0f, 1.0f,
	};

	Black::Ref<Black::VertexBuffer> vertexBuffer;
	vertexBuffer = Black::VertexBuffer::Create(vertices, sizeof(vertices));
	vertexBuffer->SetLayout({
		{ Black::ShaderDataType::Float3, "a_Position" },
		{ Black::ShaderDataType::Float4, "a_Color" }
	});

	uint32_t indices[3] = { 0, 1, 2 };
	Black::Ref<Black::IndexBuffer> indexBuffer;
	indexBuffer = Black::IndexBuffer::Create(indices, sizeof(indices));

	m_VertexArray = Black::VertexArray::Create();
	m_VertexArray->AddVertexBuffer(vertexBuffer);
	m_VertexArray->SetIndexBuffer(indexBuffer);

	std::string vertexSrc = R"(
		#version 450 core
		layout(location = 0) in vec3 a_Position;
		layout(location = 1) in vec4 a_Color;
		uniform mat4 u_ViewProjection;
		out vec4 v_Color;
		void main()
		{
			v_Color = a_Color;
			gl_Position = u_ViewProjection * vec4(a_Position, 1.0);
		}
	)";

	std::string fragmentSrc = R"(
		#version 450 core
		in vec4 v_Color;
		layout(location = 0) out vec4 color;
		void main()
		{
			color = v_Color;
		}
	)";

	m_Shader = Black::Shader::Create("TriangleShader", vertexSrc, fragmentSrc);

	// Square
	float squareVertices[4 * 7] = {
		-0.75f, -0.75f, 0.0f, 0.2f, 0.3f, 0.8f, 1.0f,
		 0.75f, -0.75f, 0.0f, 0.2f, 0.3f, 0.8f, 1.0f,
		 0.75f,  0.75f, 0.0f, 0.2f, 0.3f, 0.8f, 1.0f,
		-0.75f,  0.75f, 0.0f, 0.2f, 0.3f, 0.8f, 1.0f,
	};

	Black::Ref<Black::VertexBuffer> squareVB;
	squareVB = Black::VertexBuffer::Create(squareVertices, sizeof(squareVertices));
	squareVB->SetLayout({
		{ Black::ShaderDataType::Float3, "a_Position" },
		{ Black::ShaderDataType::Float4, "a_Color" }
	});

	uint32_t squareIndices[6] = { 0, 1, 2, 2, 3, 0 };
	Black::Ref<Black::IndexBuffer> squareIB;
	squareIB = Black::IndexBuffer::Create(squareIndices, sizeof(squareIndices));

	m_SquareVA = Black::VertexArray::Create();
	m_SquareVA->AddVertexBuffer(squareVB);
	m_SquareVA->SetIndexBuffer(squareIB);

	std::string blueVertexSrc = R"(
		#version 450 core
		layout(location = 0) in vec3 a_Position;
		uniform mat4 u_ViewProjection;
		void main()
		{
			gl_Position = u_ViewProjection * vec4(a_Position, 1.0);
		}
	)";

	std::string blueFragmentSrc = R"(
		#version 450 core
		layout(location = 0) out vec4 color;
		void main()
		{
			color = vec4(0.2, 0.3, 0.8, 1.0);
		}
	)";

	m_BlueShader = Black::Shader::Create("BlueShader", blueVertexSrc, blueFragmentSrc);
}

void ExampleLayer::OnDetach()
{
}

void ExampleLayer::OnUpdate(Black::Timestep ts)
{
	Black::RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1.0f });
	Black::RenderCommand::Clear();

	m_Camera.SetPosition({ 0.0f, 0.0f, 0.0f });
	m_Camera.SetRotation(0.0f);

	Black::Renderer::BeginScene();

	m_BlueShader->Bind();
	m_BlueShader->SetMat4("u_ViewProjection", m_Camera.GetViewProjectionMatrix());
	Black::Renderer::Submit(m_BlueShader, m_SquareVA);

	m_Shader->Bind();
	m_Shader->SetMat4("u_ViewProjection", m_Camera.GetViewProjectionMatrix());
	Black::Renderer::Submit(m_Shader, m_VertexArray);

	Black::Renderer::EndScene();
}

void ExampleLayer::OnEvent(Black::Event& event)
{
}
