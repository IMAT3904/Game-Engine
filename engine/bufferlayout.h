#pragma once
#include "include/independent/rendering/shaderdatatype.h"
#include <vector>

namespace Engine {
	class BufferElement {
	public:
		ShaderDataType datatype;
		uint32_t size;
		uint32_t offset;
		bool normalised;

		BufferElement() {};
		BufferElement(ShaderDataType newtype, bool isnormalised = false) :
			datatype(newtype),
			size(SDT::Size(newtype)),
			offset(0),
			normalised(isnormalised)
		{}
	};

	class BufferLayout {
	public:
		BufferLayout() {};
		BufferLayout(const std::initializer_list<BufferElement>& element);
		inline uint32_t GetStride() { return stride; }
		void AddElement(BufferElement element);
		inline std::vector<BufferElement>::iterator Begin() { return elements.begin(); }
		inline std::vector<BufferElement>::iterator End() { return elements.end(); }
		inline std::vector<BufferElement>::const_iterator Begin() const { return elements.begin(); }
		inline std::vector<BufferElement>::const_iterator End() const { return elements.begin(); }
	private:
		std::vector<BufferElement> elements;
		uint32_t stride;
		void CalcStrideAndOffset();
	};

	void BufferLayout::AddElement(BufferElement element) {
		elements.push_back(element);
		CalcStrideAndOffset();
	}

	void BufferLayout::CalcStrideAndOffset() {
		uint32_t offset = 0;
		for (auto& element : elements) {
			element.offset = offset;
			offset = element.size;
		}
		stride = offset;
	}
}