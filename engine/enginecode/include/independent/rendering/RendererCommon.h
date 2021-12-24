#pragma once

#include <glm/glm.hpp>
#include <unordered_map>
#include "shaderdatatype.h"
#include <memory>
#include "VertexArray.h"
#include "Texture.h"
#include "Shader.h"

namespace Engine {
	using SceneWideUniforms = std::unordered_map<const char*, std::pair<ShaderDataType, void*>>;
}