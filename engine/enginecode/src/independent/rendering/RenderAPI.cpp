#include "engine_pch.h"
#include "rendering/RenderAPI.h"
#include "rendering/IndexBuffer.h"
#include "rendering/OpenGLIndexBuffer.h"
#include "rendering/OpenGLVertexBuffer.h"
#include "rendering/VertexBuffer.h"
#include "rendering/VertexArray.h"
#include "rendering/OpenGLVertexArray.h"
#include "rendering/OpenGLShader.h"
#include "rendering/Shader.h"
#include "rendering/OpenGLTexture.h"
#include "rendering/Texture.h"
#include "rendering/OpenGLUniformBuffer.h"
#include "rendering/UniformBuffer.h"
#include "systems/log.h"

namespace Engine {
	RenderAPI::API RenderAPI::sAPI = RenderAPI::API::OpenGL;

	IndexBuffer* IndexBuffer::create(uint32_t* indices, uint32_t count) {
		switch (RenderAPI::getAPI()) {
			case RenderAPI::API::None:
				Log::error("NO RENDERING API INCLUDED");
					break;
			case RenderAPI::API::OpenGL:
				return new OpenGLIndexBuffer(indices, count);
				Log::info("OpenGL Supported");
			case RenderAPI::API::Direct3D:
				Log::error("DIRECT3D NOT SUPPORTED");
				break;
			case RenderAPI::API::Vulkan:
				Log::error("DIRECT3D NOT SUPPORTED");
				break;
		}
		return nullptr;
	}

	VertexBuffer* VertexBuffer::create(void* vertices, uint32_t size, VertexBufferLayout layout) {
		switch (RenderAPI::getAPI()) {
		case RenderAPI::API::None:
			Log::error("NO RENDERING API INCLUDED");
			break;
		case RenderAPI::API::OpenGL:
			return new OpenGLVertexBuffer(vertices, size, layout);
			Log::info("OpenGL Supported");
		case RenderAPI::API::Direct3D:
			Log::error("DIRECT3D NOT SUPPORTED");
			break;
		case RenderAPI::API::Vulkan:
			Log::error("DIRECT3D NOT SUPPORTED");
			break;
		}
		return nullptr;
	}

	VertexArray* VertexArray::create() {
		switch (RenderAPI::getAPI()) {
		case RenderAPI::API::None:
			Log::error("NO RENDERING API INCLUDED");
			break;
		case RenderAPI::API::OpenGL:
			return new OpenGLVertexArray();
			Log::info("OpenGL Supported");
		case RenderAPI::API::Direct3D:
			Log::error("DIRECT3D NOT SUPPORTED");
			break;
		case RenderAPI::API::Vulkan:
			Log::error("DIRECT3D NOT SUPPORTED");
			break;
		}
		return nullptr;
	}

	Shader* Shader::create(const char* vertexpath, const char* fragpath) {
		switch (RenderAPI::getAPI()) {
		case RenderAPI::API::None:
			Log::error("NO RENDERING API INCLUDED");
			break;
		case RenderAPI::API::OpenGL:
			return new OpenGLShader(vertexpath, fragpath);
			Log::info("OpenGL Supported");
		case RenderAPI::API::Direct3D:
			Log::error("DIRECT3D NOT SUPPORTED");
			break;
		case RenderAPI::API::Vulkan:
			Log::error("DIRECT3D NOT SUPPORTED");
			break;
		}
		return nullptr;
	}

	Shader* Shader::create(const char* filepath) {
		switch (RenderAPI::getAPI()) {
		case RenderAPI::API::None:
			Log::error("NO RENDERING API INCLUDED");
			break;
		case RenderAPI::API::OpenGL:
			return new OpenGLShader(filepath);
			Log::info("OpenGL Supported");
		case RenderAPI::API::Direct3D:
			Log::error("DIRECT3D NOT SUPPORTED");
			break;
		case RenderAPI::API::Vulkan:
			Log::error("DIRECT3D NOT SUPPORTED");
			break;
		}
		return nullptr;
	}

	Texture* Texture::create(const char* filepath) {
		switch (RenderAPI::getAPI()) {
		case RenderAPI::API::None:
			Log::error("NO RENDERING API INCLUDED");
			break;
		case RenderAPI::API::OpenGL:
			return new OpenGLTexture(filepath);
			Log::info("OpenGL Supported");
		case RenderAPI::API::Direct3D:
			Log::error("DIRECT3D NOT SUPPORTED");
			break;
		case RenderAPI::API::Vulkan:
			Log::error("DIRECT3D NOT SUPPORTED");
			break;
		}
		return nullptr;
	}

	Texture* Texture::create(uint32_t width, uint32_t height, uint32_t channels, unsigned char* data) {
		switch (RenderAPI::getAPI()) {
		case RenderAPI::API::None:
			Log::error("NO RENDERING API INCLUDED");
			break;
		case RenderAPI::API::OpenGL:
			return new OpenGLTexture(width, height, channels, data);
			Log::info("OpenGL Supported");
		case RenderAPI::API::Direct3D:
			Log::error("DIRECT3D NOT SUPPORTED");
			break;
		case RenderAPI::API::Vulkan:
			Log::error("DIRECT3D NOT SUPPORTED");
			break;
		}
		return nullptr;
	}

	UniformBuffer* UniformBuffer::create(const UniformBufferLayout& layout) {
		switch (RenderAPI::getAPI()) {
		case RenderAPI::API::None:
			Log::error("NO RENDERING API INCLUDED");
			break;
		case RenderAPI::API::OpenGL:
			return new OpenGLUniformBuffer(layout);
			Log::info("OpenGL Supported");
		case RenderAPI::API::Direct3D:
			Log::error("DIRECT3D NOT SUPPORTED");
			break;
		case RenderAPI::API::Vulkan:
			Log::error("DIRECT3D NOT SUPPORTED");
			break;
		}
		return nullptr;
	}
}