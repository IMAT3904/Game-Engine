#pragma once
#include "engine_pch.h"
#include "bufferlayout.h"
#include "OpenGLIndexBuffer.h"
#include "OpenGLVertexBuffer.h"
#include <vector>
#include <memory>
#include "systems/log.h"

/** \file VertexArray.h
*/

namespace Engine {
	/** \class VertexArray
** \brief Base class of a Vertex Array object that's pure virtual


**/
	class VertexArray {
	public:
		virtual ~VertexArray() = default; //!< Deconstructor
		virtual void AddVertexBuffer(const std::shared_ptr<VertexBuffer>& vertexbuffer) = 0; //!< Attatches a vertex buffer to the VAO
		virtual void SetIndexBuffer(const std::shared_ptr<IndexBuffer>& indexbuffer) = 0; //!< Attatches an index buffer to the VAO
		virtual inline uint32_t GetRenderID() const = 0; //!< Returns OpenGLID
		virtual inline uint32_t GetDrawCount() const = 0; //!< Returns draw count
		virtual inline std::shared_ptr<IndexBuffer> GetIndexBuffer() const = 0; //!< Returns index buffer

		static VertexArray* create(); //!< Improvised constructor
	};
}