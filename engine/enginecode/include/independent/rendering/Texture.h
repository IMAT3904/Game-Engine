#pragma once
#include <cstdint>

namespace Engine {
	class Texture {
	public:
		virtual ~Texture() = default;
		virtual void edit(uint32_t xoffset, uint32_t yoffset, uint32_t width, uint32_t height, unsigned char* data) = 0;
		virtual inline uint32_t getID() const = 0;
		virtual inline uint32_t getWidth() const = 0;
		virtual inline uint32_t getHeight() const = 0;
		virtual inline uint32_t getChannels() const = 0;

		static Texture* create(const char* filepath);
		static Texture* create(uint32_t width, uint32_t height, uint32_t channels, unsigned char* data);
	};
}