#pragma once
#include "GLFWWindowImpl.h"

namespace Engine {
	class GLFW_OpenGL_GC  : GLFWWindowImpl{
	public:
		void init();
		void swapbuffers();
	};
}