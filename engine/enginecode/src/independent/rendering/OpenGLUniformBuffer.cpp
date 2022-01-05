#include "engine_pch.h"
#include <glad/glad.h>
#include "rendering/OpenGLUniformBuffer.h"

/** \file OpenGLUniformBuffer.cpp
*/

namespace Engine {
	uint32_t OpenGLUniformBuffer::sblocknumber = 0;
	OpenGLUniformBuffer::OpenGLUniformBuffer(const UniformBufferLayout& nlayout) {
		layout = nlayout;
		blocknumber = sblocknumber;
		sblocknumber++;

		glGenBuffers(1, &OpenGLID);
		glBindBuffer(GL_UNIFORM_BUFFER, OpenGLID);
		glBufferData(GL_UNIFORM_BUFFER, layout.GetStride(), nullptr, GL_DYNAMIC_DRAW);
		glBindBufferRange(GL_UNIFORM_BUFFER, blocknumber, OpenGLID, 0, layout.GetStride());

		for (auto& element : layout) {
			uniformcache[element.name] = std::pair<uint32_t, uint32_t>(element.offset, element.size);
		}
	}

	OpenGLUniformBuffer::~OpenGLUniformBuffer() {
		glDeleteBuffers(1, &OpenGLID);
	}

	void OpenGLUniformBuffer::AttachShaderBlock(const std::shared_ptr<Shader>& shader, const char* blockname) {
		uint32_t blockindex = glGetUniformBlockIndex(shader->GetID(), blockname);
		glUniformBlockBinding(shader->GetID(), blockindex, blocknumber);
	}

	void OpenGLUniformBuffer::UploadData(const char* uniformname, void* data) {
		glBindBuffer(GL_UNIFORM_BUFFER, OpenGLID);
		auto& pair = uniformcache[uniformname];
		glBufferSubData(GL_UNIFORM_BUFFER, pair.first, pair.second, data);
	}
}