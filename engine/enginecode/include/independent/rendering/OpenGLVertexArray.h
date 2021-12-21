#pragma once
#include "engine_pch.h"
#include "bufferlayout.h"
#include "OpenGLIndexBuffer.h"
#include "OpenGLVertexBuffer.h"
#include <vector>
#include <memory>
#include "systems/log.h"
#include "VertexArray.h"

namespace Engine {
	class OpenGLVertexArray : public VertexArray{
	public:
		OpenGLVertexArray();
		virtual ~OpenGLVertexArray();
		virtual void AddVertexBuffer(const std::shared_ptr<VertexBuffer>& vertexbuffer) override;
		virtual void SetIndexBuffer(const std::shared_ptr<IndexBuffer>& indexbuffer) override;
		virtual inline uint32_t GetRenderID() const override { return OpenGLID; }
		virtual inline uint32_t GetDrawCount() const override{ if (indexbuffer) { return indexbuffer->GetCount(); } else { return 0; Log::error("nothing to draw"); } }
	private:
		uint32_t OpenGLID;
		uint32_t attributeindex = 0;
		std::vector<std::shared_ptr<VertexBuffer>> vertexbuffer;
		std::shared_ptr<IndexBuffer> indexbuffer;
	};
}