#include "include/independent/rendering/OpenGLVertexBuffer.h"
#include <glad/glad.h>
#include "engine_pch.h"

namespace Engine {
	void BufferLayout::AddElement(BufferElement element) {
		elements.push_back(element);
		CalcStrideAndOffset();
	}

	void BufferLayout::CalcStrideAndOffset() {
		uint32_t offset = 0;
		for (auto& element : elements) {
			element.offset = offset;
			offset = element.size;
		}
		stride = offset;
	}
	OpenGLVertexBuffer::OpenGLVertexBuffer(void* vertices, uint32_t size, BufferLayout layout) {
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