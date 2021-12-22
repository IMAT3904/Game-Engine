/** \file renderer3D.cpp */
#include "engine_pch.h"
#include "rendering/Renderer3D.h"

namespace Engine {
	std::shared_ptr<Renderer3D::InternalData> Renderer3D::data = nullptr;

	void Renderer3D::init() {
		data.reset(new InternalData);
		unsigned char whitepixel[4] = { 255,255,255,255 };
		data->defaulttexture.reset(Texture::create(1, 1, 4, whitepixel));
		data->defaulttint = { 1.0f,1.0f,1.0f,1.0f };
	}

	void Renderer3D::begin(const SceneWideUniforms& scenewideuniforms) {
		data->scenewideuniforms = scenewideuniforms;
	}

	void Renderer3D::submit(const std::shared_ptr<VertexArray>& geometry, const std::shared_ptr<Material>& material, const glm::mat4& model) {

	}

	void Renderer3D::end() {
		data->scenewideuniforms.clear();
	}
}