#pragma once
#include <glm/glm.hpp>
#include <GLFW/glfw3.h>

/** \file inputpoller.h
*/

namespace Engine {
	/** \class InputPoller
** \brief A class to detect specific events


**/
	class InputPoller {
	public:
		static bool iskeypressed(int keycode); //!< when key is pressed
		static bool ismousebuttonpressed(int button); //!< when mouse button is pressed
		static glm::vec2 getmouseposition(); //!< output mouse position
		inline static float getmousex() { return getmouseposition().x; } //!< get mouse x
		inline static float getmousey() { return getmouseposition().y; } //!< get mouse y
		static void setcurrentwindow(void* newwin); //!< set current window
	};
}