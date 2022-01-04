#include "engine_pch.h"
#include "platform/GLFWInputPoller.h"
#include <GLFW/glfw3.h>
/** \file GLFWInputPoller.cpp
*/
namespace Engine {
	GLFWwindow* GLFWInputPoller::window = nullptr;
	bool GLFWInputPoller::iskeypressed(int32_t keycode) {
		if (window) {
			auto answer = glfwGetKey(window, keycode);
			return answer == GLFW_PRESS || answer == GLFW_REPEAT;
		}
		return false;
	}

	bool GLFWInputPoller::ismousebuttonpressed(int32_t mousebutton) {
		if (window) {
			auto answer = glfwGetMouseButton(window, mousebutton);
			return answer == GLFW_PRESS || answer == GLFW_REPEAT;
		}
		return false;
	}

	glm::vec2 GLFWInputPoller::getmouseposition() {
		if (window) {
			double x, y;
			glfwGetCursorPos(window, &x, &y);
			return glm::vec2(static_cast<float>(x), static_cast<float>(y));
		}
		return {-1.f,-1.f};
	}
}