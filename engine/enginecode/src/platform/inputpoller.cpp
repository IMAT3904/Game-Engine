#include "engine_pch.h"
#include "..\..\include\platform\inputpoller.h"

namespace Engine {
	GLFWwindow* InputPoller::window = nullptr;
	bool InputPoller::iskeypressed(int keycode){
		if (window) {
			auto answer = glfwGetKey(window, keycode);
			return answer == GLFW_PRESS || answer == GLFW_REPEAT;
		}
		return false;
	}

	bool InputPoller::ismousebuttonpressed(int button) {
		if (window) {
			auto answer = glfwGetMouseButton(window, button);
			return answer == GLFW_PRESS;
		}
		return false;
	}

	glm::vec2 InputPoller::getmouseposition() {
		if (window) {
			double x, y;
			glfwGetCursorPos(window, &x, &y);
			return glm::vec2(static_cast<float>(x), static_cast<float>(y));
		}
		return { -1.f,-1.f };
	}
}