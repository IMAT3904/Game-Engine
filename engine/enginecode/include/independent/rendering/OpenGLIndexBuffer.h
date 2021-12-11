#pragma once
#include <cstdint>
namespace Engine {
	class OpenGLIndexBuffer {
	public:
		OpenGLIndexBuffer(uint32_t* indices, uint32_t count);
		~OpenGLIndexBuffer();
		inline uint32_t GetRenderID() const { return OpenGLID; }
		inline uint32_t GetCount() const { return count; }
	private:
		uint32_t OpenGLID;
		uint32_t count;
	};
}