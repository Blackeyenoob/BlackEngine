#pragma once

#include "Black/Core.h"
#include "Black/Events/Event.h"
#include "Black/Events/ApplicationEvent.h"
#include "Black/Events/KeyEvent.h"
#include "Black/Events/MouseEvent.h"
#include "Black/Timestep.h"

namespace Black {

	class BLACK_API Layer
	{
	public:
		Layer(const std::string& name = "Layer");
		virtual ~Layer() = default;

		virtual void OnAttach() {}
		virtual void OnDetach() {}
		virtual void OnUpdate(Timestep ts) {}
		virtual void OnImGuiRender() {}
		virtual void OnEvent(Event& event) {}

		inline const std::string& GetName() const { return m_DebugName; }
	protected:
		std::string m_DebugName;
	};

}
