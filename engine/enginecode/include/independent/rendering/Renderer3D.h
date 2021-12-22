#pragma once

#include <glm/glm.hpp>
#include <unordered_map>
#include <memory>
#include "VertexArray.h"
#include "Texture.h"
#include "Shader.h"
#include "shaderdatatype.h"
#include "RenderAPI.h"

namespace Engine {
	using SceneWideUniforms = std::unordered_map<const char*, std::pair<ShaderDataType, void*>>;

	class Material;

	/** \class Renderer3D
	** \brief A class which renders a 3D scene using geometry (is non batched)
	
	
	**/

	class Renderer3D {
	public:
		static void init(); //!< Initalize 3D renderer
		static void begin(const SceneWideUniforms& scenewideuniforms); //!< Create a new 3D scene
		static void submit(const std::shared_ptr<VertexArray>& geometry, const std::shared_ptr<Material>& material, const glm::mat4& model); //!< Submit data
		static void end(); //!< End scene
	private:
		struct InternalData {
			SceneWideUniforms scenewideuniforms; //!< Replace with UBO at some point
			std::shared_ptr<Texture> defaulttexture; //!< default white texture
			glm::vec4 defaulttint; //!< default tint
		};

		static std::shared_ptr<InternalData> data; //!< Holds internal data
	};
}