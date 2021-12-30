#pragma once

#include <glm/glm.hpp>
#include <unordered_map>
#include "shaderdatatype.h"
#include <memory>
#include "VertexArray.h"
#include "Texture.h"
#include "Shader.h"
#include "RenderCommands.h"

namespace Engine {
	using SceneWideUniforms = std::unordered_map<const char*, std::pair<ShaderDataType, void*>>;

	class RendererCommon {
	public:
		static void actioncommand(std::shared_ptr<RenderCommand>& command) { command->action(); }
	};
}