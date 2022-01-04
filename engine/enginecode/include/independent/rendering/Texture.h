#pragma once
#include <cstdint>

/** \file Texture.h
*/

namespace Engine {
	/** \class Texture
** \brief Base class of a Texture object that's pure virtual


**/
	class Texture {
	public:
		virtual ~Texture() = default; //!< Deconstructor
		virtual void edit(uint32_t xoffset, uint32_t yoffset, uint32_t width, uint32_t height, unsigned char* data) = 0; //!< Constructor with data paramaters that modify the object
		virtual inline uint32_t getID() const = 0; //!< Gets OpenGLID
		virtual inline uint32_t getWidth() const = 0; //!< Gets width
		virtual inline uint32_t getHeight() const = 0; //!< Gets height
		virtual inline uint32_t getChannels() const = 0; //!< Gets channels

		static Texture* create(const char* filepath); //!< Improvised constructor that takes 1 filepath that creates an object
		static Texture* create(uint32_t width, uint32_t height, uint32_t channels, unsigned char* data); //!< Improvised constructor that creates a new texture using a width, height, channels and texture data
	};
}