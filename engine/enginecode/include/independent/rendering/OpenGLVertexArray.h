#pragma once
#include "bufferlayout.h"
#include "OpenGLIndexBuffer.h"
#include "OpenGLVertexBuffer.h"
#include <vector>
#include <memory>

namespace Engine {
	class OpenGLVertexArray {
	public:
		OpenGLVertexArray();
		~OpenGLVertexArray();
		void AddVertexBuffer(const std::shared_ptr<OpenGLVertexBuffer>& vertexbuffer);
		void SetIndexBuffer(const std::shared_ptr<OpenGLIndexBuffer>& indexbuffer);
		inline uint32_t GetRenderID() const { return OpenGLID; }\
		inline uint32_t GetDrawCount() { if (indexbuffer) { return indexbuffer->GetCount(); } else { return 0; } }
	private:
		uint32_t OpenGLID;
		uint32_t attributeindex = 0;
		std::vector<std::shared_ptr<OpenGLVertexBuffer>> vertexbuffer;
		std::shared_ptr<OpenGLIndexBuffer> indexbuffer;
	};
}