#pragma once
#include "engine_pch.h"
#include "rendering/bufferlayout.h"
#include <glad/glad.h>
#include "VertexBuffer.h"

namespace Engine {
	class OpenGLVertexBuffer : public VertexBuffer{
	public:
		OpenGLVertexBuffer(void* vertices, uint32_t size, VertexBufferLayout layout);
		virtual ~OpenGLVertexBuffer();
		virtual void edit(void* vertices, uint32_t size, uint32_t offset) override;
		virtual inline uint32_t GetRenderID() const override { return OpenGLID; }
		virtual inline const VertexBufferLayout& GetLayout() const override { return layout; }
	private:
		uint32_t OpenGLID;
		VertexBufferLayout layout;
	};
}