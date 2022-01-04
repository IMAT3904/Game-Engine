#pragma once
#include "rendering/graphicsContext.h"
#include <GLFW/glfw3.h>

/** \file GLFW_OpenGL_GC.h
*/

namespace Engine {
	/** \class GLFW_OpenGL_GC
** \brief A GLFW base class for graphics context


**/
	class GLFW_OpenGL_GC  : public GraphicsContext {
	public:
		GLFW_OpenGL_GC::GLFW_OpenGL_GC(GLFWwindow* window) : m_window(window){} //!< constructor that takes a GLFW Window
		void init() override; //!< initialise the graphics context
		void swapbuffers() override; //!< swag the buffers from the graphics context
	private:
		GLFWwindow* m_window; //!< a GLFW window
	};
}