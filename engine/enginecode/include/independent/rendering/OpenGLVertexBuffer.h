#pragma once
#include "engine_pch.h"
#include "rendering/bufferlayout.h"
#include <glad/glad.h>
#include "VertexBuffer.h"

/** \file OpenGLVertexBuffer.h
*/

namespace Engine {
	/** \class OpenGLVertexBuffer
** \brief OpenGL iteration of a vertex buffer object that overrides the pure virtual VertexBuffer class


**/
	class OpenGLVertexBuffer : public VertexBuffer{
	public:
		OpenGLVertexBuffer(void* vertices, uint32_t size, VertexBufferLayout layout); //!< Constructor that takes vertices, size and VertexBufferLayout
		virtual ~OpenGLVertexBuffer(); //!< Deconstructor
		virtual void edit(void* vertices, uint32_t size, uint32_t offset) override; //!< edit the object with vertices, size and offset
		virtual inline uint32_t GetRenderID() const override { return OpenGLID; } //!< returns OpenGLID
		virtual inline const VertexBufferLayout& GetLayout() const override { return layout; } //!< returns VertexBufferLayout
	private:
		uint32_t OpenGLID;
		VertexBufferLayout layout; //!< VertexBufferLayout
	};
}