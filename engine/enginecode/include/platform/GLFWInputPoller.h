#pragma once
#include <glm/glm.hpp>
#include <GLFW/glfw3.h>

/** \file GLFWInputPoller.h
*/

namespace Engine {
	/** \class GLFWInputPoller
** \brief A GLFW based class that activates upon actions being made


**/
	class GLFWInputPoller {
	public:
		static bool iskeypressed(int keycode); //!< when key is pressed
		static bool ismousebuttonpressed(int button); //!< when mouse button is pressed
		static glm::vec2 getmouseposition(); //!< output mouse position
		inline static float getmousex() { return getmouseposition().x; } //!< get mouse x
		inline static float getmousey() { return getmouseposition().y; } //!< get mouse y
		static void setcurrentwindow(GLFWwindow* newwin) { window = newwin; } //!< set current window
	private:
		static GLFWwindow* window; //!< GLFW Window
	};
}