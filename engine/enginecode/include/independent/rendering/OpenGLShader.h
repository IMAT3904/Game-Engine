#pragma once
#include <glm/glm.hpp>
#include <cstdint>

namespace Engine {
	class OpenGLShader {
	public:
		OpenGLShader(const char* vertexpath, const char* fragpath);
		OpenGLShader(const char* filepath);
		~OpenGLShader();
		uint32_t GetID() const { return OpenGLID; }
		void UploadInt(const char* name, int value);
		void UploadFloat(const char* name, float value);
		void UploadFloat2(const char* name, const glm::vec2& value);
		void UploadFloat3(const char* name, const glm::vec3& value);
		void UploadFloat4(const char* name, const glm::vec4& value);
		void UploadMat4(const char* name, const glm::mat4& value);
	private:
		uint32_t OpenGLID;
		void CompileAndLink(const char* vertexpath, const char* fragpath);
	};
}