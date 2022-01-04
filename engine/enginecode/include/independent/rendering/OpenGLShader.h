#pragma once
#include <glm/glm.hpp>
#include <cstdint>
#include "Shader.h"

/** \file OpenGLShader.h
*/

namespace Engine {
	/** \class OpenGLShader
** \brief OpenGL iteration of a shader object that overrides the pure virtual Shader class


**/
	class OpenGLShader : public Shader{
	public:
		OpenGLShader(const char* vertexpath, const char* fragpath); //!< Constructor with 2 filepaths
		OpenGLShader(const char* filepath); //!< Constructor with 1 filepath
		virtual ~OpenGLShader(); //!< Deconstructor
		virtual uint32_t GetID() const override { return OpenGLID; } //!< Returns OpenGLID
		virtual void UploadInt(const char* name, int value) override; //!< Uploads an int
		virtual void UploadFloat(const char* name, float value) override; //!< Uploads a float
		virtual void UploadFloat2(const char* name, const glm::vec2& value) override; //!< Uploads a vec2
		virtual void UploadFloat3(const char* name, const glm::vec3& value) override; //!< Uploads a vec3
		virtual void UploadFloat4(const char* name, const glm::vec4& value) override; //!< Uploads a vec4
		virtual void UploadMat4(const char* name, const glm::mat4& value) override; //!< Uploads a mat4
	private:
		uint32_t OpenGLID;
		void CompileAndLink(const char* vertexpath, const char* fragpath); //!< Compiles and links the vertex shader and the fragment shader
	};
}