#pragma once
#include <cstdint>
#include <glm/glm.hpp>

/** \file Shader.h
*/

namespace Engine {
	/** \class IndexBuffer
** \brief Base class of a Shader object that's pure virtual


**/
	class Shader {
	public:
		virtual ~Shader() = default; //!< Deconstructor
		virtual uint32_t GetID() const = 0; //!< returns ID
		virtual void UploadInt(const char* name, int value) = 0; //!< Uploads an int
		virtual void UploadFloat(const char* name, float value) = 0; //!< Uploads a float
		virtual void UploadFloat2(const char* name, const glm::vec2& value) = 0; //!< Uploads a vec2
		virtual void UploadFloat3(const char* name, const glm::vec3& value) = 0; //!< Uploads a vec3
		virtual void UploadFloat4(const char* name, const glm::vec4& value) = 0; //!< Uploads a vec4
		virtual void UploadMat4(const char* name, const glm::mat4& value) = 0; //!< Uploads a mat4

		static Shader* create(const char* vertexpath, const char* fragpath); //!< Improvised constructor that takes 2 filepaths that creates an object
		static Shader* create(const char* filepath); //!< Improvised constructor that takes 1 filepath that creates an object
	};
}