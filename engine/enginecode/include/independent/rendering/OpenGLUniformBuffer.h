#pragma once

#include "bufferlayout.h"
#include "Shader.h"
#include <unordered_map>
#include <memory>
#include "UniformBuffer.h"

namespace Engine {
	class OpenGLUniformBuffer : public  UniformBuffer {
	public:
		OpenGLUniformBuffer(const UniformBufferLayout& layout);
		~OpenGLUniformBuffer();
		inline uint32_t GetRenderID() override { return OpenGLID; }
		inline UniformBufferLayout GetLayout() override { return layout; }
		void AttachShaderBlock(const std::shared_ptr<Shader>& shader, const char* blockname) override;
		void UploadData(const char* uniformname, void* data) override;
	private:
		uint32_t OpenGLID;
		static uint32_t sblocknumber; //!< Global block number
	};
}