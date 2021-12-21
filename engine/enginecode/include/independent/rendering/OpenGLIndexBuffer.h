#pragma once
#include "engine_pch.h"
#include <cstdint>
#include "IndexBuffer.h"
namespace Engine {
	class OpenGLIndexBuffer  : public IndexBuffer{
	public:
		OpenGLIndexBuffer(uint32_t* indices, uint32_t count);
		virtual ~OpenGLIndexBuffer();
		virtual inline uint32_t GetRenderID() const override{ return OpenGLID; }
		virtual inline uint32_t GetCount() const override{ return count; }
	private:
		uint32_t OpenGLID;
		uint32_t count;
	};
}