#pragma once
#include <ctype.h>
#include "bufferlayout.h"
#include "Shader.h"
#include <memory>
#include <unordered_map>

namespace Engine {
	class UniformBuffer {
	public:
		virtual ~UniformBuffer() = default;
		virtual inline uint32_t GetRenderID() = 0;
		virtual inline UniformBufferLayout GetLayout() = 0;
		virtual void AttachShaderBlock(const std::shared_ptr<Shader>& shader, const char* blockname) = 0;
		virtual void UploadData(const char* uniformname, void* data) = 0;

		static UniformBuffer* create(const UniformBufferLayout& layout);
	protected:
		UniformBufferLayout layout;
		std::unordered_map<const char*, std::pair<uint32_t, uint32_t>> uniformcache;
		uint32_t blocknumber; //!< Block number for this UBO
	};
}