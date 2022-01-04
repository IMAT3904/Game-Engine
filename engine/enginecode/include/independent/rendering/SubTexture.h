#pragma once
#include "rendering/OpenGLTexture.h"
#include <memory>
#include <glm/glm.hpp>

/** \file SubTexture.h
*/

namespace Engine {
	/** \class SubTexture
** \brief Allows for a subtexture to be added to a texture


**/
	class SubTexture {
	public:
		SubTexture(); //!< Default constructor
		SubTexture(const std::shared_ptr<OpenGLTexture>& ntexture, const glm::vec2& nUVStart, const glm::vec2& nUVEnd); //!< Constructor with a texture with the UVstart and UVend of the texture
		inline glm::vec2 GetUVStart() { return UVStart; } //!< Gets the beginning of the UV
		inline glm::vec2 GetUVSEnd() { return UVEnd; } //!< Gets the end of the UV
		inline glm::ivec2 GetSize() { return size; } //!< Gets the size
		inline glm::vec2 GetFSize() { return { static_cast<float>(size.x),static_cast<float>(size.y) }; } //!< Gets the size in float form
		inline uint32_t GetWidth() { return size.x; } //!< Gets the size on the x axis
		inline uint32_t GetHeight() { return size.y; } //!< Gets the size on the y axis
		inline uint32_t GetWidthF() { return static_cast<float>(size.x); } //!< Gets the size on the x axis as a float
		inline uint32_t GetHeightF() { return static_cast<float>(size.y); } //!< Gets the size on the y axis as a float
		float transformU(float U); //!< Transform the U value
		float transformV(float V); //!< Transform the V value
		glm::vec2 transformUV(glm::vec2 UV);
	private:
		std::shared_ptr<OpenGLTexture> texture; //!< The texture
		glm::vec2 UVStart; //!< The UV start
		glm::vec2 UVEnd; //!< The UV end
		glm::ivec2 size; //!< The size
	};
}