#include "engine_pch.h"
#include "rendering/bufferlayout.h"

namespace Engine {
	void BufferLayout::AddElement(BufferElement element) {
		elements.push_back(element);
		CalcStrideAndOffset();
	}

	void BufferLayout::CalcStrideAndOffset() {
		uint32_t offset = 0;
		for (auto& element : elements) {
			element.offset += offset;
			offset += element.size;
		}
		stride = offset;
	}
}