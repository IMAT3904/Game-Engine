#include "engine_pch.h"
#include <glad/glad.h>
#include "rendering/OpenGLIndexBuffer.h"

namespace Engine {
	OpenGLIndexBuffer::OpenGLIndexBuffer(uint32_t* indices, uint32_t lcount) : count(lcount) {
		glCreateBuffers(1, &OpenGLID);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, OpenGLID);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(uint32_t) * count, indices, GL_STATIC_DRAW);
	}

	OpenGLIndexBuffer::~OpenGLIndexBuffer() {
		glDeleteBuffers(1, &OpenGLID);
	}
}