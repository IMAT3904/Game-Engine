#include "engine_pch.h"
#include "rendering/OpenGLVertexBuffer.h"

namespace Engine {
	OpenGLVertexBuffer::OpenGLVertexBuffer(void* vertices, uint32_t size, BufferLayout newlayout) : layout(newlayout){
		layout = newlayout;
		glCreateBuffers(1, &OpenGLID);
		glBindBuffer(GL_ARRAY_BUFFER, OpenGLID);
		glBufferData(GL_ARRAY_BUFFER, size, vertices, GL_DYNAMIC_DRAW);
	}

	OpenGLVertexBuffer::~OpenGLVertexBuffer() {
		glDeleteBuffers(1, &OpenGLID);
	}

	void OpenGLVertexBuffer::edit(void* vertices,uint32_t size, uint32_t offset) {
		glBindBuffer(GL_ARRAY_BUFFER, OpenGLID);
		glBufferSubData(GL_ARRAY_BUFFER, offset, size, vertices);
	}
}