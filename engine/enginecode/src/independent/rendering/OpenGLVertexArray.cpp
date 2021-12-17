#include "engine_pch.h"
#include <glad/glad.h>
#include "rendering/OpenGLVertexArray.h"

namespace Engine {
	namespace SDT {
		static GLenum ToGLType(ShaderDataType type) {
			switch (type) {
			case ShaderDataType::Float: return GL_FLOAT;
			case ShaderDataType::Float2: return GL_FLOAT;
			case ShaderDataType::Float3: return GL_FLOAT;
			case ShaderDataType::Float4: return GL_FLOAT;
			default: return GL_INVALID_ENUM;
			}
		}
	}
	OpenGLVertexArray::OpenGLVertexArray() {
		glCreateVertexArrays(1, &OpenGLID);
		glBindVertexArray(OpenGLID);
	}

	OpenGLVertexArray::~OpenGLVertexArray() {
		glDeleteVertexArrays(1, &OpenGLID);
	}

	void OpenGLVertexArray::AddVertexBuffer(const std::shared_ptr<OpenGLVertexBuffer>& newvertexbuffer) {
		glBindVertexArray(OpenGLID);
		glBindBuffer(GL_ARRAY_BUFFER, newvertexbuffer->GetRenderID());

		auto layout = newvertexbuffer->GetLayout();

		for (auto& element: layout) {
			uint32_t normalised = GL_FALSE;
			if (element.normalised) { normalised = GL_TRUE; }
			glEnableVertexAttribArray(attributeindex);
			glVertexAttribPointer(
				attributeindex,
				SDT::ComponentCount(element.datatype),
				SDT::ToGLType(element.datatype),
				normalised,
				layout.GetStride(),
				(void*)element.offset
			);
			attributeindex++;
		}
	}

	void OpenGLVertexArray::SetIndexBuffer(const std::shared_ptr<OpenGLIndexBuffer>& newindexbuffer) {
		indexbuffer = newindexbuffer;
	}
}