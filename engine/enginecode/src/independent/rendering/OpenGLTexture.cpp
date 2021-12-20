#include "engine_pch.h"
#include "rendering/OpenGLTexture.h"
#include <glad/glad.h>

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

namespace Engine {
	OpenGLTexture::OpenGLTexture(const char* filepath) {
		int nwidth, nheight, nchannels;
		unsigned char* data = stbi_load(filepath, &nwidth, &nheight, &nchannels, 0);
		if (data) { init(nwidth, nheight, nchannels, data); }
		stbi_image_free(data);
	}

	OpenGLTexture::OpenGLTexture(uint32_t nwidth, uint32_t nheight, uint32_t nchannels, unsigned char* data) {
		if (data) { init(nwidth, nheight, nchannels, data); }
	}

	OpenGLTexture::~OpenGLTexture() {
		glDeleteTextures(1, &OpenGLID);
	}

	void OpenGLTexture::edit(uint32_t xoffset, uint32_t yoffset, uint32_t nwidth, uint32_t nheight, unsigned char* data) {
		glBindTexture(GL_TEXTURE_2D, OpenGLID);
		if (data) {
			if (channels == 3) glTextureSubImage2D(GL_TEXTURE_2D,0,xoffset,yoffset,nwidth,nheight,GL_RGB,GL_UNSIGNED_BYTE,data);
			else if (channels == 4) glTextureSubImage2D(GL_TEXTURE_2D, 0, xoffset, yoffset, nwidth, nheight, GL_RGBA, GL_UNSIGNED_BYTE, data);
		}
	}

	void OpenGLTexture::init(uint32_t nwidth, uint32_t nheight, uint32_t nchannels, unsigned char* data) {
		glGenTextures(1, &OpenGLID);
		glBindTexture(GL_TEXTURE_2D, OpenGLID);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		if (nchannels == 3) glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, nwidth, nheight, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
		else if (nchannels == 4) glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, nwidth, nheight, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
		else return;
		glGenerateMipmap(GL_TEXTURE_2D);

		width = nwidth;
		height = nheight;
		channels = nchannels;
	}
}