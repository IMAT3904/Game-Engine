#pragma once
#include "rendering/OpenGLTexture.h"
#include <memory>
#include <glm/glm.hpp>

namespace Engine {
	class SubTexture {
	public:
		SubTexture();
		SubTexture(const std::shared_ptr<OpenGLTexture>& ntexture, const glm::vec2& nUVStart, const glm::vec2& nUVEnd);
		inline glm::vec2 GetUVStart() { return UVStart; }
		inline glm::vec2 GetUVSEnd() { return UVEnd; }
		inline glm::ivec2 GetSize() { return size; }
		inline glm::vec2 GetFSize() { return { static_cast<float>(size.x),static_cast<float>(size.y) }; }
		inline uint32_t GetWidth() { return size.x; }
		inline uint32_t GetHeight() { return size.y; }
		inline uint32_t GetWidthF() { return static_cast<float>(size.x); }
		inline uint32_t GetHeightF() { return static_cast<float>(size.y); }
		float transformU(float U);
		float transformV(float V);
		glm::vec2 transformUV(glm::vec2 UV);
	private:
		std::shared_ptr<OpenGLTexture> texture;
		glm::vec2 UVStart;
		glm::vec2 UVEnd;
		glm::ivec2 size;
	};
}