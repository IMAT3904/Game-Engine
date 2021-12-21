#pragma once
#include "rendering/bufferlayout.h"
#include <cstdint>

namespace Engine {
	class VertexBuffer {
	public:
		virtual ~VertexBuffer() = default;
		virtual void edit(void* vertices, uint32_t size, uint32_t offset) = 0;
		virtual inline uint32_t GetRenderID() const = 0;
		virtual inline const BufferLayout& GetLayout() const = 0;

		static VertexBuffer* create(void* vertices, uint32_t size, BufferLayout layout);
	};
}