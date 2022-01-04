#pragma once
#include "RenderAPI.h"
#include "RendererCommon.h"

/** \file Renderer3D.h
*/

namespace Engine {
	/** \class Material
	** \brief Holds a shader and uniforms for said shader


	**/
	class Material {
	public:
		Material(const std::shared_ptr<Shader>& nshader) : //!< Constructor with a shader
			shader(nshader), flags(0), texture(nullptr), tint(glm::vec4(0.0f))
		{}
		Material(const std::shared_ptr<Shader>& nshader, const std::shared_ptr<Texture>& ntexture, const glm::vec4& ntint) :
			shader(nshader), texture(ntexture), tint(ntint)
		{
			SetFlags(flag_texture | flag_tint);
		}

		Material(const std::shared_ptr<Shader>& nshader, const std::shared_ptr<Texture>& ntexture) : //!< Constructor with a shader and a texture
			shader(nshader), texture(ntexture), tint(glm::vec4(0.0f))
		{
			SetFlags(flag_texture);
		}

		Material(const std::shared_ptr<Shader>& nshader, const glm::vec4& ntint) : //!< Constructor with a shader and a tint
			shader(nshader), texture(nullptr), tint(ntint)
		{
			SetFlags(flag_tint);
		}

		inline std::shared_ptr<Shader> GetShader() const { return shader; } //!< Returns the shader
		inline std::shared_ptr<Texture> GetTexture() const { return texture; } //!< Returns the texture
		inline glm::vec4 GetTint() const { return tint; } //!< Returns the tint
		bool IsFlagSet(uint32_t flag) const { return flags& flag; } //!< Returns if the flag is set 

		void SetTexture(const std::shared_ptr<Texture>& ntexture) { texture = ntexture; } //!< Sets a new texture
		void SetTexture(const glm::vec4& ntint) { tint = ntint; } //!< Sets a new texture using the tint


		constexpr static uint32_t flag_texture = 1 << 0; //!< 00000001
		constexpr static uint32_t flag_tint = 1 << 1; //!< 00000010

	private:
		uint32_t flags = 0; //!< a bitfield representation of shader settings
		std::shared_ptr<Shader> shader; //!< shader attached to material
		std::shared_ptr<Texture> texture; //!< texture attached to material
		glm::vec4 tint;  //!< tint attached to material
		void SetFlags(uint32_t flag) { flags = flags | flag; }
	};


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