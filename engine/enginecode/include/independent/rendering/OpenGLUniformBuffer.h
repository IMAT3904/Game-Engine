#pragma once

#include "bufferlayout.h"
#include "Shader.h"
#include <unordered_map>
#include <memory>
#include "UniformBuffer.h"

/** \file OpenGLUniformBuffer.h
*/

namespace Engine {
	/** \class OpenGLUniformBuffer
** \brief OpenGL iteration of a uniform buffer object that allows uniforms to be implemented in blocks


**/
	class OpenGLUniformBuffer : public  UniformBuffer {
	public:
		OpenGLUniformBuffer(const UniformBufferLayout& layout); //!< Constructor with layout
		~OpenGLUniformBuffer(); //!< Deconstructor
		inline uint32_t GetRenderID() override { return OpenGLID; } //!< Gets OpenGLID
		inline UniformBufferLayout GetLayout() override { return layout; } //!< Returns layout
		void AttachShaderBlock(const std::shared_ptr<Shader>& shader, const char* blockname) override; //!< Allows a shader to be attatched with the name of the block where the uniforms will be stored
		void UploadData(const char* uniformname, void* data) override; //!< Upload data to the uniform block  with param name and data
	private:
		uint32_t OpenGLID;
		static uint32_t sblocknumber; //!< Global block number
	};
}