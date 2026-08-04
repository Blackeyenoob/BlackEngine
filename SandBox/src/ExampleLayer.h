#pragma once

#include "Black/Layer.h"
#include "Black/Timestep.h"
#include "Black/Events/Event.h"
#include "Black/Renderer/Shader.h"
#include "Black/Renderer/VertexArray.h"
#include "Black/Renderer/OrthographicCamera.h"

class ExampleLayer : public Black::Layer
{
public:
	ExampleLayer();
	virtual ~ExampleLayer() = default;

	virtual void OnAttach() override;
	virtual void OnDetach() override;
	virtual void OnUpdate(Black::Timestep ts) override;
	virtual void OnEvent(Black::Event& event) override;

private:
	Black::Ref<Black::Shader> m_Shader;
	Black::Ref<Black::VertexArray> m_VertexArray;

	Black::Ref<Black::Shader> m_BlueShader;
	Black::Ref<Black::VertexArray> m_SquareVA;

	Black::OrthographicCamera m_Camera;
};
