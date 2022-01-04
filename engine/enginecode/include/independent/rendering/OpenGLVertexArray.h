#pragma once
#include "engine_pch.h"
#include "bufferlayout.h"
#include "OpenGLIndexBuffer.h"
#include "OpenGLVertexBuffer.h"
#include <vector>
#include <memory>
#include "systems/log.h"
#include "VertexArray.h"

/** \file OpenGLVertexArray.h
*/

namespace Engine {
	/** \class OpenGLVertexArray
** \brief OpenGL iteration of a Vertex Array


**/
	class OpenGLVertexArray : public VertexArray{
	public:
		OpenGLVertexArray(); //!< Constructor
		virtual ~OpenGLVertexArray(); //!< Deconstructor
		virtual void AddVertexBuffer(const std::shared_ptr<VertexBuffer>& vertexbuffer) override; //!< Attatches a vertex buffer to the VAO
		virtual void SetIndexBuffer(const std::shared_ptr<IndexBuffer>& indexbuffer) override; //!< Attatches an index buffer to the VAO
		virtual inline uint32_t GetRenderID() const override { return OpenGLID; } //!< Returns OpenGLID
		virtual inline uint32_t GetDrawCount() const override{ if (indexbuffer) { return indexbuffer->GetCount(); } else { return 0; Log::error("nothing to draw"); } } //!< Returns draw count
		virtual inline std::shared_ptr<IndexBuffer> GetIndexBuffer() const override { return indexbuffer; } //!< Returns index buffer
	private:
		uint32_t OpenGLID;
		uint32_t attributeindex = 0; //!< Attribute count
		std::vector<std::shared_ptr<VertexBuffer>> vertexbuffer; //!< VBO
		std::shared_ptr<IndexBuffer> indexbuffer; //!< IBO
	};
}