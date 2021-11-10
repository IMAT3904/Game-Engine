#include "include/platform/GLFW_OpenGL_GC.h"
#include "engine_pch.h"
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "systems/log.h"

namespace Engine {
	void GLFW_OpenGL_GC::init() {
		glEnable(GL_DEBUG_OUTPUT);
		glDebugMessageCallback(
			[](
				GLenum source,
				GLenum type,
				GLuint id,
				GLenum severity,
				GLsizei length,
				const GLchar* message,
				const void* userParam
				)
			{
			switch (severity) {
				case GL_DEBUG_SEVERITY_HIGH:
					Log::error(message);
					break;
				case GL_DEBUG_SEVERITY_MEDIUM:
					Log::warn(message);
					break;
				case GL_DEBUG_SEVERITY_LOW:
					Log::info(message);
					break;
				case GL_DEBUG_SEVERITY_NOTIFICATION:
					Log::trace(message);
					break;
				}
			}
		,nullptr);
	}

	void GLFW_OpenGL_GC::swapbuffers() {

	}
}