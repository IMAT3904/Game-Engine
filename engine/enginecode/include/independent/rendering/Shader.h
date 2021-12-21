#pragma once
#include <cstdint>
#include <glm/glm.hpp>

namespace Engine {
	class Shader {
	public:
		virtual ~Shader() = default;
		virtual uint32_t GetID() const = 0;
		virtual void UploadInt(const char* name, int value) = 0;
		virtual void UploadFloat(const char* name, float value) = 0;
		virtual void UploadFloat2(const char* name, const glm::vec2& value) = 0;
		virtual void UploadFloat3(const char* name, const glm::vec3& value) = 0;
		virtual void UploadFloat4(const char* name, const glm::vec4& value) = 0;
		virtual void UploadMat4(const char* name, const glm::mat4& value) = 0;

		static Shader* create(const char* vertexpath, const char* fragpath);
		static Shader* create(const char* filepath);
	};
}