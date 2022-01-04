#pragma once
#include <ctype.h>
#include "bufferlayout.h"
#include "Shader.h"
#include <memory>
#include <unordered_map>

/** \file UniformBuffer.h
*/

namespace Engine {
	/** \class UniformBuffer
** \brief Base class of a Uniform Buffer object that's pure virtual


**/
	class UniformBuffer {
	public:
		virtual ~UniformBuffer() = default; //!< Deconstructor
		virtual inline uint32_t GetRenderID() = 0; //!< Gets OpenGLID
		virtual inline UniformBufferLayout GetLayout() = 0; //!< Returns layout
		virtual void AttachShaderBlock(const std::shared_ptr<Shader>& shader, const char* blockname) = 0; //!< Allows a shader to be attatched with the name of the block where the uniforms will be stored
		virtual void UploadData(const char* uniformname, void* data) = 0; //!< Upload data to the uniform block  with param name and data

		static UniformBuffer* create(const UniformBufferLayout& layout); //!< Improvised constructor that takes a uniform buffer layout to create an object
	protected:
		UniformBufferLayout layout; //!< Uniform buffer layout
		std::unordered_map<const char*, std::pair<uint32_t, uint32_t>> uniformcache; //!< Uniform Buffer cache
		uint32_t blocknumber; //!< Block number for this UBO
	};
}