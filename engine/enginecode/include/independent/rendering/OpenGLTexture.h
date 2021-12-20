#pragma once

#include <cstdint>

namespace Engine {
	class OpenGLTexture {
	public:
		OpenGLTexture(const char* filepath);
		OpenGLTexture(uint32_t width, uint32_t height, uint32_t channels, unsigned char* data);
		~OpenGLTexture();
		void edit(uint32_t xoffset, uint32_t yoffset, uint32_t width, uint32_t height, unsigned char* data);
		inline uint32_t getID() { return OpenGLID; }
		inline uint32_t getWidth() { return width; }
		inline uint32_t getHeight() { return height; }
		inline uint32_t getChannels() { return channels; }
	private:
		uint32_t OpenGLID;
		uint32_t width;
		uint32_t height;
		uint32_t channels;
		void init(uint32_t width, uint32_t height, uint32_t channels, unsigned char* data);
	};
}