#pragma once
#include <cstdint>

namespace Engine {
	class IndexBuffer {
	public:
		virtual ~IndexBuffer();
		virtual inline uint32_t GetRenderID() const { return OpenGLID; }
		virtual inline uint32_t GetCount() const { return count; }
	private:
		uint32_t OpenGLID;
		uint32_t count;
	}
}