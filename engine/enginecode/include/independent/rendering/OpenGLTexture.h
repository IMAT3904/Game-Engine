#pragma once

#include <cstdint>
#include "Texture.h"

namespace Engine {
	class OpenGLTexture : public Texture{
	public:
		OpenGLTexture(const char* filepath);
		OpenGLTexture(uint32_t width, uint32_t height, uint32_t channels, unsigned char* data);
		virtual ~OpenGLTexture();
		virtual void edit(uint32_t xoffset, uint32_t yoffset, uint32_t width, uint32_t height, unsigned char* data) override;
		virtual inline uint32_t getID() const override { return OpenGLID; }
		virtual inline uint32_t getWidth() const override { return width; }
		virtual inline uint32_t getHeight() const override { return height; }
		virtual inline uint32_t getChannels() const override { return channels; }
	private:
		uint32_t OpenGLID;
		uint32_t width;
		uint32_t height;
		uint32_t channels;
		void init(uint32_t width, uint32_t height, uint32_t channels, unsigned char* data);
	};
}