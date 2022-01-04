#pragma once
#include <cstdint>

/** \file IndexBuffer.h
*/

namespace Engine {
	/** \class IndexBuffer
** \brief Base class of an index buffer object that's pure virtual


**/
	class IndexBuffer {
	public:
		virtual ~IndexBuffer() = default; //!< Deconstructor
		virtual inline uint32_t GetRenderID() const = 0; //!< Returns RenderID
		virtual inline uint32_t GetCount() const = 0; //!< Returns the count

		static IndexBuffer* create(uint32_t* indices, uint32_t count); //!< Improvised constructor that creates an object
	};
}