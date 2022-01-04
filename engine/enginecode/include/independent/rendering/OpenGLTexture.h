#pragma once

#include <cstdint>
#include "Texture.h"

/** \file OpenGLTexture.h
*/

namespace Engine {
	/** \class OpenGLTexture
** \brief OpenGL iteration of a texture object that overrides the pure virtual Texture class


**/
	class OpenGLTexture : public Texture{
	public:
		OpenGLTexture(const char* filepath); //!< Constructor with a filepath
		OpenGLTexture(uint32_t width, uint32_t height, uint32_t channels, unsigned char* data); //!< Constructor with data paramaters that modify the object
		virtual ~OpenGLTexture(); //!< Deconstructor
		virtual void edit(uint32_t xoffset, uint32_t yoffset, uint32_t width, uint32_t height, unsigned char* data) override; //!< Modifies the existing object that can offset and change the data of the texture
		virtual inline uint32_t getID() const override { return OpenGLID; } //!< Gets OpenGLID
		virtual inline uint32_t getWidth() const override { return width; } //!< Gets width
		virtual inline uint32_t getHeight() const override { return height; } //!< Gets height
		virtual inline uint32_t getChannels() const override { return channels; } //!< Gets channels
	private:
		uint32_t OpenGLID;
		uint32_t width; 
		uint32_t height;
		uint32_t channels;
		void init(uint32_t width, uint32_t height, uint32_t channels, unsigned char* data);
	};
}