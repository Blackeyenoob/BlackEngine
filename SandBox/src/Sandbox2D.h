#pragma once

#include "Black.h"

class Sandbox2D : public Black::Layer
{
public:
	Sandbox2D();
	virtual ~Sandbox2D() = default;

	virtual void OnAttach() override;
	virtual void OnDetach() override;

	void OnUpdate(Black::Timestep ts) override;
	virtual void OnImGuiRender() override;
	void OnEvent(Black::Event& e) override;
private:
	Black::OrthographicCameraController m_CameraController;
	
	// Temp
	Black::Ref<Black::VertexArray> m_SquareVA;
	Black::Ref<Black::Shader> m_FlatColorShader;

	Black::Ref<Black::Texture2D> m_CheckerboardTexture;

	glm::vec4 m_SquareColor = { 0.2f, 0.3f, 0.8f, 1.0f };
};