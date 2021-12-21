#pragma once
#include "engine_pch.h"
#include "bufferlayout.h"
#include "OpenGLIndexBuffer.h"
#include "OpenGLVertexBuffer.h"
#include <vector>
#include <memory>
#include "systems/log.h"

namespace Engine {
	class OpenGLVertexArray {
	public:
		OpenGLVertexArray();
		~OpenGLVertexArray();
		void AddVertexBuffer(const std::shared_ptr<VertexBuffer>& vertexbuffer);
		void SetIndexBuffer(const std::shared_ptr<IndexBuffer>& indexbuffer);
		inline uint32_t GetRenderID() const { return OpenGLID; }
		inline uint32_t GetDrawCount() { if (indexbuffer) { return indexbuffer->GetCount(); } else { return 0; Log::error("nothing to draw"); } }
	private:
		uint32_t OpenGLID;
		uint32_t attributeindex = 0;
		std::vector<std::shared_ptr<VertexBuffer>> vertexbuffer;
		std::shared_ptr<IndexBuffer> indexbuffer;
	};
}