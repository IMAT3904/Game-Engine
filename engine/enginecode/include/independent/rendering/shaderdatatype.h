#pragma once
#include "engine_pch.h"
#include <stdint.h>
#include <vector>

namespace Engine {
	enum class ShaderDataType {
		None = 0,Float,Float2,Float3,Float4,Int,Mat4
	};

	namespace SDT {
		static uint32_t Size(ShaderDataType type) {
			switch (type) {
				case ShaderDataType::Float:return 4;
				case ShaderDataType::Int:return 4;
				case ShaderDataType::Float2:return 4 * 2;
				case ShaderDataType::Float3:return 4 * 3;
				case ShaderDataType::Float4:return 4 * 4;
				case ShaderDataType::Mat4:return 4 * 4 * 4;
				default: return 0;
			}
		}

		static uint32_t ComponentCount(ShaderDataType type) {
			switch (type) {
				case ShaderDataType::Int:return 1;
				case ShaderDataType::Float:return 1;
				case ShaderDataType::Float2:return 2;
				case ShaderDataType::Float3:return 3;
				case ShaderDataType::Float4:return 4;
				case ShaderDataType::Mat4:return 4*4;
				default: return 0;
			}
		}
	}
}