#pragma once
#include <cstdint>

namespace Engine {
	class IndexBuffer {
	public:
		virtual ~IndexBuffer() = default;
		virtual inline uint32_t GetRenderID() const = 0;
		virtual inline uint32_t GetCount() const = 0;

		static IndexBuffer* create(uint32_t* indices, uint32_t count);
	};
}