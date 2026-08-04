#include "bkpch.h"
#include "Black/Input.h"
#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
#include "Black/Application.h"

namespace Black {

	static GLFWwindow* GetGLFWWindow() {
		auto* window = static_cast<GLFWwindow*>(
			((Black::Application::Get()).GetWindow().GetNativeWindow())
		);
		return window;
	}

	bool Input::IsKeyPressed(int keycode) {
		auto* window = GetGLFWWindow();
		int state = glfwGetKey(window, keycode);
		return state == GLFW_PRESS || state == GLFW_REPEAT;
	}

	bool Input::IsMouseButtonPressed(int button) {
		auto* window = GetGLFWWindow();
		int state = glfwGetMouseButton(window, button);
		return state == GLFW_PRESS;
	}

	std::pair<float, float> Input::GetMousePosition() {
		auto* window = GetGLFWWindow();
		double xpos, ypos;
		glfwGetCursorPos(window, &xpos, &ypos);
		return { (float)xpos, (float)ypos };
	}

	float Input::GetMouseX() {
		auto [x, y] = GetMousePosition();
		return x;
	}

	float Input::GetMouseY() {
		auto [x, y] = GetMousePosition();
		return y;
	}

}
