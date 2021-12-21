#pragma once
#include "engine_pch.h"
#include "rendering/bufferlayout.h"
#include <glad/glad.h>
#include "VertexBuffer.h"

namespace Engine {
	class OpenGLVertexBuffer : public VertexBuffer{
	public:
		OpenGLVertexBuffer(void* vertices, uint32_t size, BufferLayout layout);
		virtual ~OpenGLVertexBuffer();
		virtual void edit(void* vertices, uint32_t size, uint32_t offset);
		virtual inline uint32_t GetRenderID() const { return OpenGLID; }
		virtual inline const BufferLayout& GetLayout() const { return layout; }
	private:
		uint32_t OpenGLID;
		BufferLayout layout;
	};
}