#pragma once
#include "bufferlayout.h"
#include "engine_pch.h"
namespace Engine {
	class OpenGLVertexBuffer {
	public:
		OpenGLVertexBuffer(void* vertices, uint32_t size, BufferLayout layout);
		~OpenGLVertexBuffer();
		void edit(void* vertices, uint32_t size, uint32_t offset);
		inline uint32_t GetRenderID() const { return OpenGLID; }
		inline const BufferLayout& GetLayout() const { return layout; }
	private:
		uint32_t OpenGLID;
		BufferLayout layout;
	};
}