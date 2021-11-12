#pragma once
#include "rendering/graphicsContext.h"
#include <GLFW/glfw3.h>

namespace Engine {
	class GLFW_OpenGL_GC  : public GraphicsContext {
	public:
		GLFW_OpenGL_GC::GLFW_OpenGL_GC(GLFWwindow* window) : m_window(window){}
		void init() override;
		void swapbuffers() override;
	private:
		GLFWwindow* m_window;
	};
}