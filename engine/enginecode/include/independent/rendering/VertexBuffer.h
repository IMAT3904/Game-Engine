#pragma once
#include "rendering/bufferlayout.h"
#include <cstdint>

/** \file VertexBuffer.h
*/

namespace Engine {
	/** \class VertexBuffer
** \brief Base class of a Vertex Buffer object that's pure virtual


**/
	class VertexBuffer {
	public:
		virtual ~VertexBuffer() = default; //!< Deconstructor
		virtual void edit(void* vertices, uint32_t size, uint32_t offset) = 0; //!< edit the object with vertices, size and offset
		virtual inline uint32_t GetRenderID() const = 0; //!< returns OpenGLID
		virtual inline const VertexBufferLayout& GetLayout() const = 0; //!< returns VertexBufferLayout

		static VertexBuffer* create(void* vertices, uint32_t size, VertexBufferLayout layout); //!< Improvised constructor that takes the vertices, size and vertex buffer layout to create an object
	};
}