#pragma once

#include <glm/glm.hpp>
#include <unordered_map>
#include "shaderdatatype.h"
#include <memory>
#include "VertexArray.h"
#include "Texture.h"
#include "Shader.h"
#include "RenderCommands.h"

/** \file RendererCommon.h
*/

namespace Engine {
	/** \class RendererCommon
** \brief Allows an action to be performed and holds header files


**/
	using SceneWideUniforms = std::unordered_map<const char*, std::pair<ShaderDataType, void*>>;

	class RendererCommon {
	public:
		static void actioncommand(std::shared_ptr<RenderCommand>& command) { command->action(); } //!< Actives an action
	};
}