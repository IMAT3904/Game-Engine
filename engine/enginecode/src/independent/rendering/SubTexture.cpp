#include "engine_pch.h"
#include "rendering/SubTexture.h"

namespace Engine {
	SubTexture::SubTexture(const std::shared_ptr<OpenGLTexture>& ntexture, const glm::vec2& nUVStart, const glm::vec2& nUVEnd) :
	texture(ntexture),
	UVStart(nUVStart),
	UVEnd(nUVEnd)
	{
		size.x = static_cast<int>((UVEnd.x - UVStart.x) * texture->getWidth());
		size.y = static_cast<int>((UVEnd.y - UVStart.y) * texture->getHeight());
	}

	float SubTexture::transformU(float U) {
		return UVStart.x + ((UVEnd.x) * U);
	}

	float SubTexture::transformV(float V) {
		return UVStart.y + ((UVEnd.y) * V);
	}

	glm::vec2 SubTexture::transformUV(glm::vec2 UV) {
		return UVStart + ((UVEnd) * UV);
	}
}