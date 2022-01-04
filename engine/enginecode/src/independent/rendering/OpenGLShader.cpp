#include "engine_pch.h"
#include "rendering/OpenGLShader.h"
#include <string>
#include <fstream>
#include "systems/log.h"
#include <array>
#include <glad/glad.h>
#include <glm/gtc/type_ptr.hpp>

/** \file OpenGLShader.cpp
*/

namespace Engine {
	OpenGLShader::OpenGLShader(const char* vertexpath, const char* fragpath) {
		Log::info("Loaded at path: {0}", vertexpath);
		Log::info("Loaded at path: {0}", fragpath);
		std::string line, vertexsrc, fragsrc;
		std::fstream handle(vertexpath, std::ios::in);
		if (handle.is_open()) {
			while (getline(handle, line)) { vertexsrc += (line + "\n"); }
		}
		else {
			Log::error("Could not open vertex source: {0}", vertexpath);
			return;
		}
		handle.close();

		handle.open(fragpath, std::ios::in);
		if (handle.is_open()) {
			while (getline(handle, line)) { fragsrc += (line + "\n"); }
		}
		else {
			Log::error("Could not open fragment source: {0}", fragpath);
			return;
		}
		handle.close();
		CompileAndLink(vertexsrc.c_str(), fragsrc.c_str());
	}

	OpenGLShader::OpenGLShader(const char* filepath) {
		Log::info("Loaded at path: {0}", filepath);
		enum Region{ None = -1, Vertex = 0, Frag = 1, Geometry, TessellationControl, TessellationEvaluation, Compute };
		std::string line;
		std::array<std::string, Region::Compute + 1> filesrc;
		uint32_t region = Region::None;
		std::fstream handle(filepath, std::ios::in);
		if (handle.is_open()) {
			while (getline(handle, line)) { 
				if (line.find("#region Vertex") != std::string::npos) { region = Region::Vertex; continue; }
				if (line.find("#region Frag") != std::string::npos) { region = Region::Frag; continue; }
				if (line.find("#region Geometry") != std::string::npos) { region = Region::Geometry; continue; }
				if (line.find("#region TessellationControl") != std::string::npos) { region = Region::TessellationControl; continue; }
				if (line.find("#region TessellationEvaluation") != std::string::npos) { region = Region::TessellationEvaluation; continue;}
				if (line.find("#region Compute") != std::string::npos) { region = Region::Compute; continue;}

				if (region != Region::None) { filesrc[region] += (line + "\n"); }
			}
		}
		else {
			Log::error("Could not open shader source: {0}", filepath);
			return;
		}
		handle.close();
		CompileAndLink(filesrc[Region::Vertex].c_str(), filesrc[Region::Frag].c_str());
	}

	OpenGLShader::~OpenGLShader() {
		glDeleteShader(OpenGLID);
	}

	void OpenGLShader::UploadInt(const char* name, int value) {
		uint32_t uniformLocation = glGetUniformLocation(OpenGLID, name);
		glUniform1i(uniformLocation, value);
	}

	void OpenGLShader::UploadFloat(const char* name, float value) {
		uint32_t uniformLocation = glGetUniformLocation(OpenGLID, name);
		glUniform1f(uniformLocation, value);
	}

	void OpenGLShader::UploadFloat2(const char* name, const glm::vec2& value) {
		uint32_t uniformLocation = glGetUniformLocation(OpenGLID, name);
		glUniform2f(uniformLocation, value.x, value.y);
	}

	void OpenGLShader::UploadFloat3(const char* name, const glm::vec3& value) {
		uint32_t uniformLocation = glGetUniformLocation(OpenGLID, name);
		glUniform3f(uniformLocation, value.x, value.y, value.z);
	}

	void OpenGLShader::UploadFloat4(const char* name, const glm::vec4& value) {
		uint32_t uniformLocation = glGetUniformLocation(OpenGLID, name);
		glUniform4f(uniformLocation, value.x, value.y, value.z,value.w);
	}

	void OpenGLShader::UploadMat4(const char* name, const glm::mat4& value) {
		uint32_t uniformLocation = glGetUniformLocation(OpenGLID, name);
		glUniformMatrix4fv(uniformLocation, 1, GL_FALSE, glm::value_ptr(value));
	}

	void OpenGLShader::CompileAndLink(const char* vertexpath, const char* fragpath) {
		GLuint vertexshader = glCreateShader(GL_VERTEX_SHADER);

		const GLchar* source = vertexpath;
		glShaderSource(vertexshader, 1, &source, 0);
		glCompileShader(vertexshader);

		GLint isCompiled = 0;
		glGetShaderiv(vertexshader, GL_COMPILE_STATUS, &isCompiled);
		if (isCompiled == GL_FALSE)
		{
			GLint maxLength = 0;
			glGetShaderiv(vertexshader, GL_INFO_LOG_LENGTH, &maxLength);

			std::vector<GLchar> infoLog(maxLength);
			glGetShaderInfoLog(vertexshader, maxLength, &maxLength, &infoLog[0]);
			Log::error("Shader compile error: {0}", std::string(infoLog.begin(), infoLog.end()));

			glDeleteShader(vertexshader);
			return;
		}

		GLuint fragshader = glCreateShader(GL_FRAGMENT_SHADER);

		source = fragpath;
		glShaderSource(fragshader, 1, &source, 0);
		glCompileShader(fragshader);

		glGetShaderiv(fragshader, GL_COMPILE_STATUS, &isCompiled);
		if (isCompiled == GL_FALSE)
		{
			GLint maxLength = 0;
			glGetShaderiv(fragshader, GL_INFO_LOG_LENGTH, &maxLength);

			std::vector<GLchar> infoLog(maxLength);
			glGetShaderInfoLog(fragshader, maxLength, &maxLength, &infoLog[0]);
			Log::error("Shader compile error: {0}", std::string(infoLog.begin(), infoLog.end()));

			glDeleteShader(fragshader);
			glDeleteShader(vertexshader);

			return;
		}

		OpenGLID = glCreateProgram();
		glAttachShader(OpenGLID, vertexshader);
		glAttachShader(OpenGLID, fragshader);
		glLinkProgram(OpenGLID);

		GLint isLinked = 0;
		glGetProgramiv(OpenGLID, GL_LINK_STATUS, (int*)&isLinked);
		if (isLinked == GL_FALSE)
		{
			GLint maxLength = 0;
			glGetProgramiv(OpenGLID, GL_INFO_LOG_LENGTH, &maxLength);

			std::vector<GLchar> infoLog(maxLength);
			glGetProgramInfoLog(OpenGLID, maxLength, &maxLength, &infoLog[0]);
			Log::error("Shader linking error: {0}", std::string(infoLog.begin(), infoLog.end()));

			glDeleteProgram(OpenGLID);
			glDeleteShader(vertexshader);
			glDeleteShader(fragshader);

			return;
		}

		glDetachShader(OpenGLID, vertexshader);
		glDetachShader(OpenGLID, fragshader);
	}
}