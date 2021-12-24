#pragma once
#include "RendererCommon.h"
namespace Engine {
	class Quad {

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