#pragma once
#include "RendererCommon.h"
#include "ft2build.h"
#include "freetype/freetype.h"
namespace Engine {
	class Quad {
	public:
		Quad() = default;
		static Quad CreateCentreHalfExtents(const glm::vec2& centre, const glm::vec2& halfextents);
	private:
		glm::vec3 translate = glm::vec3(0.0f);
		glm::vec3 scale = glm::vec3(1.0f);
		friend class Renderer2D;
	};

	class Renderer2D {
	public:
		static void init();
		static void begin(const SceneWideUniforms& swu);
		static void submit(const Quad& quad, const glm::vec4& tint); //!< render a tinted quad
		static void submit(const Quad& quad, const std::shared_ptr<Texture>& texture); //!< render a textured quad
		static void submit(const Quad& quad, const glm::vec4& tint, const std::shared_ptr<Texture>& texture); //!< render a textured and tinted quad
		static void submit(const Quad& quad, const glm::vec4& tint, float angle, bool degrees = false); //!< render a tinted quad that's angled
		static void submit(const Quad& quad, const std::shared_ptr<Texture>& texture, float angle, bool degrees = false); //!< render a textured quad that's angled
		static void submit(const Quad& quad, const glm::vec4& tint, const std::shared_ptr<Texture>& texture, float angle, bool degrees = false); //!< render a textured and tinted quad that's angled
		
		static void submit(char ch, glm::vec2& position, float& advance, const glm::vec4 tint);

		static void end();
	private:
		struct InternalData {
			std::shared_ptr<Texture> defaulttexture;
			glm::vec4 defaulttint;
			std::shared_ptr<Shader> shader;
			std::shared_ptr<VertexArray> VAO;
			glm::mat4 model;
			FT_Library ft;
			FT_Face fontface;
			std::shared_ptr<Texture> fonttexture;
			glm::ivec2 glyphbufferdims;
			uint32_t glyphbuffersize;
			std::shared_ptr<unsigned char> glyphbuffer;
		};

		static std::shared_ptr<InternalData> data;

		static unsigned char* RtoRGBA(unsigned char* RBuffer, uint32_t width, uint32_t height);
	};
}