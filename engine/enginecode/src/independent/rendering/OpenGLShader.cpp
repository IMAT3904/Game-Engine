#include "engine_pch.h"
#include "rendering/OpenGLShader.h"
#include <string>
#include <fstream>
#include "systems/log.h"
#include <array>

namespace Engine {
	OpenGLShader::OpenGLShader(const char* vertexpath, const char* fragpath) {
		std::string line, vertexsrc, fragsrc;
		std::fstream handle(vertexpath, std::ios::in);
		if (handle.is_open()) {
			while (getline(handle, line)) { vertexsrc += line; }
		}
		else {
			Log::error("Could not open vertex source: {0}", vertexpath);
			return;
		}

		std::fstream handle(fragpath, std::ios::in);
		if (handle.is_open()) {
			while (getline(handle, line)) { fragsrc += line; }
		}
		else {
			Log::error("Could not open fragment source: {0}", fragpath);
			return;
		}
		CompileAndLink(vertexsrc.c_str(), fragsrc.c_str());
	}

	OpenGLShader::OpenGLShader(const char* filepath) {
		enum Region{ None = -1, Vertex = 0, Frag = 1, Geometry, TessellationControl, TessellationEvaluation, Compute };
		std::string line, std::array<std::string, Region::Compute + 1> filesrc;
		uint32_t region = Region::None;
		std::fstream handle(filepath, std::ios::in);
		if (handle.is_open()) {
			if (line.find("#region Vertex") != std::string::npos) { region = Region::Vertex; }
			if (line.find("#region Frag") != std::string::npos) { region = Region::Frag; }
			if (line.find("#region Geometry") != std::string::npos) { region = Region::Geometry; }
			if (line.find("#region TessellationControl") != std::string::npos) { region = Region::TessellationControl; }
			if (line.find("#region TessellationEvaluation") != std::string::npos) { region = Region::TessellationEvaluation; }
			if (line.find("#region Compute") != std::string::npos) { region = Region::Compute; }
			while (getline(handle, line)) { filesrc[region] += line; }
		}
		else {
			Log::error("Could not open shader source: {0}", filepath);
			return;
		}
		CompileAndLink(filesrc[Region::Vertex].c_str(), filesrc[Region::Frag].c_str());
	}

	OpenGLShader::~OpenGLShader() {

	}
}