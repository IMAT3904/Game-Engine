#pragma once
#include <glm/glm.hpp>
#include <GLFW/glfw3.h>

namespace Engine {
	class GLFWInputPoller {
	public:
		static bool iskeypressed(int keycode);
		static bool ismousebuttonpressed(int button);
		static glm::vec2 getmouseposition();
		inline static float getmousex() { return getmouseposition().x; }
		inline static float getmousey() { return getmouseposition().y; }
		static void setcurrentwindow(GLFWwindow* newwin) { window = newwin; }
	private:
		static GLFWwindow* window;
	};
}