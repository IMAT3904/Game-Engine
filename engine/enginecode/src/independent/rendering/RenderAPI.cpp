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

	VertexBuffer* VertexBuffer::create(void* vertices, uint32_t size, BufferLayout layout) {
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
}