#pragma once

#include "Black.h"

class ExampleLayer : public Black::Layer
{
public:
	ExampleLayer();
	virtual ~ExampleLayer() = default;

	virtual void OnAttach() override;
	virtual void OnDetach() override;

	void OnUpdate(Black::Timestep ts) override;
	virtual void OnImGuiRender() override;
	void OnEvent(Black::Event& e) override;
private:
	Black::ShaderLibrary m_ShaderLibrary;
	Black::Ref<Black::Shader> m_Shader;
	Black::Ref<Black::VertexArray> m_VertexArray;

	Black::Ref<Black::Shader> m_FlatColorShader;
	Black::Ref<Black::VertexArray> m_SquareVA;

	Black::Ref<Black::Texture2D> m_Texture, m_ChernoLogoTexture;

	Black::OrthographicCameraController m_CameraController;
	glm::vec3 m_SquareColor = { 0.2f, 0.3f, 0.8f };
};

