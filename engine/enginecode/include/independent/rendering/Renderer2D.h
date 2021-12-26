#pragma once
#include "RendererCommon.h"
#include <glm/gtc/matrix_transform.hpp>
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
		static void submit(const Quad& quad, const glm::vec4& tint);
		static void end();
	private:
		struct InternalData {
			std::shared_ptr<Texture> defaulttexture;
			glm::vec4 defaulttint;
			std::shared_ptr<Shader> shader;
			std::shared_ptr<VertexArray> VAO;
			glm::mat4 model;
		};

		static std::shared_ptr<InternalData> data;
	};
}