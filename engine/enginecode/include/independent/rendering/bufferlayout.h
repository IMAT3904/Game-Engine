#pragma once
#include "shaderdatatype.h"

/** \file bufferlayout.h
*/

namespace Engine {
	/** \class VertexBufferElement
** \brief Holds data of a single element in a vertex buffer


**/
	class VertexBufferElement {
	public:
		ShaderDataType datatype;
		uint32_t size;
		uint32_t offset;
		bool normalised;

		VertexBufferElement() {}; //!< Constructor without params
		VertexBufferElement(ShaderDataType datatype, bool normalised = false) :
			datatype(datatype),
			size(SDT::Size(datatype)),
			offset(0),
			normalised(normalised)
		{} //!< Constructor with params
	};

	/** \class UniformBufferElement
** \brief Holds data of a single element in a uniform buffer


**/
	class UniformBufferElement {
	public:
		const char* name;
		ShaderDataType datatype;
		uint32_t size;
		uint32_t offset;

		UniformBufferElement() {}; //!< Constructor without params
		UniformBufferElement(const char* nname, ShaderDataType datatype) :
			name(nname),
			datatype(datatype),
			size(SDT::Size(datatype)),
			offset(0)
		{} //!< Constructor with params
	};

	/** \class BufferLayout
** \brief Holds data of the layout that includes elements


**/
	template <class G>
	class BufferLayout {
	public:
		BufferLayout<G>() {}; //!< Constructor without params
		BufferLayout<G>(const std::initializer_list<G>& element) : elements(element) { CalcStrideAndOffset(); }; //!< Constructor with params
		inline uint32_t GetStride() const { return stride; } //!< Returns the stride of the layout
		void AddElement(G element); //!< Adds a single element
		void CalcStrideAndOffset(); //!< Calculates the offset of the buffer as well as the required stride
		inline typename std::vector<G>::iterator begin() { return elements.begin(); } //!< begins the iteration
		inline typename std::vector<G>::iterator end() { return elements.end(); } //!< ends the iteration
		inline typename std::vector<G>::const_iterator begin() const { return elements.begin(); } //!< begins the iteration as a constant
		inline typename std::vector<G>::const_iterator end() const { return elements.begin(); } //!< ends the iteration as a constant
	private:
		std::vector<G> elements;
		uint32_t stride;
	};

	template <class G>
	void BufferLayout<G>::AddElement(G element) {
		elements.push_back(element);
		CalcStrideAndOffset();
	}

	template <class G>
	void BufferLayout<G>::CalcStrideAndOffset() {
		uint32_t offset = 0;
		for (auto& element : elements) {
			element.offset += offset;
			offset += element.size;
		}
		stride = offset;
	}

	using VertexBufferLayout = BufferLayout<VertexBufferElement>;
	using UniformBufferLayout = BufferLayout<UniformBufferElement>;
}