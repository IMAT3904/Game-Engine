#pragma once
#include "engine_pch.h"
#include "bufferlayout.h"
#include "OpenGLIndexBuffer.h"
#include "OpenGLVertexBuffer.h"
#include <vector>
#include <memory>
#include "systems/log.h"

namespace Engine {
	class VertexArray {
	public:
		virtual ~VertexArray() = default;
		virtual void AddVertexBuffer(const std::shared_ptr<VertexBuffer>& vertexbuffer) = 0;
		virtual void SetIndexBuffer(const std::shared_ptr<IndexBuffer>& indexbuffer) = 0;
		virtual inline uint32_t GetRenderID() const = 0;
		virtual inline uint32_t GetDrawCount() const = 0;

		static VertexArray* create();
	};
}