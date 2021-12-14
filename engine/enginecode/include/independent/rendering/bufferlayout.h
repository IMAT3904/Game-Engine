#pragma once
#include "shaderdatatype.h"

namespace Engine {
	class BufferElement {
	public:
		ShaderDataType datatype;
		uint32_t size;
		uint32_t offset;
		bool normalised;

		BufferElement() {};
		BufferElement(ShaderDataType datatype, bool normalised = false) :
			datatype(datatype),
			size(SDT::Size(datatype)),
			offset(0),
			normalised(normalised)
		{}
	};

	class BufferLayout {
	public:
		BufferLayout() {};
		BufferLayout(const std::initializer_list<BufferElement>& element) : elements(element) { CalcStrideAndOffset(); };
		inline uint32_t GetStride() const { return stride; }
		void AddElement(BufferElement element);
		void CalcStrideAndOffset();
		inline std::vector<BufferElement>::iterator begin() { return elements.begin(); }
		inline std::vector<BufferElement>::iterator end() { return elements.end(); }
		inline std::vector<BufferElement>::const_iterator begin() const { return elements.begin(); }
		inline std::vector<BufferElement>::const_iterator end() const { return elements.begin(); }
	private:
		std::vector<BufferElement> elements;
		uint32_t stride;
	};
}