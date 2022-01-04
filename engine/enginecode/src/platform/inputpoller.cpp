#include "engine_pch.h"
#include "..\..\include\platform\inputpoller.h"
#ifdef NG_PLATFORM_WINDOWS
#include "platform/GLFWInputPoller.h"
#endif // NG_PLATFORM_WINDOWS

/** \file inputpoller.cpp
*/

namespace Engine {
#ifdef NG_PLATFORM_WINDOWS
	bool InputPoller::iskeypressed(int keycode){
		return GLFWInputPoller::iskeypressed(keycode);
	}

	bool InputPoller::ismousebuttonpressed(int mousebutton) {
		return GLFWInputPoller::ismousebuttonpressed(mousebutton);
	}

	glm::vec2 InputPoller::getmouseposition() {
		return GLFWInputPoller::getmouseposition();
	}

	void InputPoller::setcurrentwindow(void* nativewin) {
		GLFWInputPoller::setcurrentwindow(reinterpret_cast<GLFWwindow*>(nativewin));
	}
#endif // NG_PLATFORM_WINDOWS
}