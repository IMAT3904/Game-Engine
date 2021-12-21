#pragma once
#include <glm/glm.hpp>
#include <cstdint>
#include "Shader.h"

namespace Engine {
	class OpenGLShader : public Shader{
	public:
		OpenGLShader(const char* vertexpath, const char* fragpath);
		OpenGLShader(const char* filepath);
		virtual ~OpenGLShader();
		virtual uint32_t GetID() const override { return OpenGLID; }
		virtual void UploadInt(const char* name, int value) override;
		virtual void UploadFloat(const char* name, float value) override;
		virtual void UploadFloat2(const char* name, const glm::vec2& value) override;
		virtual void UploadFloat3(const char* name, const glm::vec3& value) override;
		virtual void UploadFloat4(const char* name, const glm::vec4& value) override;
		virtual void UploadMat4(const char* name, const glm::mat4& value) override;
	private:
		uint32_t OpenGLID;
		void CompileAndLink(const char* vertexpath, const char* fragpath);
	};
}