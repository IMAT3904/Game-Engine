#pragma once
#include "engine_pch.h"
#include <cstdint>
#include "IndexBuffer.h"
/** \file OpenGLIndexBuffer.h
*/

namespace Engine {
	/** \class OpenGLIndexBuffer
** \brief OpenGL iteration of an index buffer object that overrides the pure virtual IndexBuffer class


**/
	class OpenGLIndexBuffer  : public IndexBuffer{
	public:
		OpenGLIndexBuffer(uint32_t* indices, uint32_t count); //!< Constructor
		virtual ~OpenGLIndexBuffer(); //!< Deconstructor
		virtual inline uint32_t GetRenderID() const override{ return OpenGLID; } //!< Returns RenderID
		virtual inline uint32_t GetCount() const override{ return count; } //!< Returns the count
	private:
		uint32_t OpenGLID;
		uint32_t count;
	};
}