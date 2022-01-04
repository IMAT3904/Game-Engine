#pragma once
#include "RendererCommon.h"
#include "ft2build.h"
#include "freetype/freetype.h"
/** \file Renderer2D.h
*/

namespace Engine {
	/** \class Quad
** \brief A 2D quad that allows the 2D renderer to display things to the screen


**/
	class Quad {
	public:
		Quad() = default; //!< the default constructor
		static Quad CreateCentreHalfExtents(const glm::vec2& centre, const glm::vec2& halfextents); //!< creates the points on the quad from the centre and half extents 
	private:
		glm::vec3 translate = glm::vec3(0.0f); //!< the translation vector
		glm::vec3 scale = glm::vec3(1.0f); //!< the scale vector 
		friend class Renderer2D;
	};

	/** \class Renderer2D
** \brief The 2D renderer itself


**/
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
		
		static void submit(char ch, glm::vec2& position, float& advance, const glm::vec4& tint); //!< render a single character 
		static void submit(const char* text, glm::vec2& position, const glm::vec4& tint); //!< render a string

		static void end();
	private:
		struct InternalData { //!< data held in the 2D renderer
			std::shared_ptr<Texture> defaulttexture; //!< 2D texture
			glm::vec4 defaulttint; //!< default tint
			std::shared_ptr<Shader> shader; //!< default shader
			std::shared_ptr<VertexArray> VAO; //!< vertex array
			glm::mat4 model; //!< model
			FT_Library ft; //!< FT Library
			FT_Face fontface; //!< the fontface
			std::shared_ptr<Texture> fonttexture; //!< the texture of the font
			glm::ivec2 glyphbufferdims; //!< the glyph buffer dimensions
			uint32_t glyphbuffersize; //!< the size of the glyph  buffer
			std::shared_ptr<unsigned char> glyphbuffer; //!< the glyph buffer
		};

		static std::shared_ptr<InternalData> data; //!< the data object

		static void RtoRGBA(unsigned char* RBuffer, uint32_t width, uint32_t height); //!< R to RGBA
	};
}