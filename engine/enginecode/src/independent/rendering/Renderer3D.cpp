#include "engine_pch.h"
#include "rendering/Renderer3D.h"
/** \file renderer3D.cpp */

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
		//Bind Shader
		glUseProgram(material->GetShader()->GetID());
		//Apply SceneWideUniforms
		for (auto& datapair : data->scenewideuniforms) {
			const char* nameofuniform = datapair.first;
			ShaderDataType& sdt = datapair.second.first;
			void* addressofvalue = datapair.second.second;

			switch (sdt) {
			case ShaderDataType::Int:
				material->GetShader()->UploadInt(nameofuniform, *(int*)addressofvalue);
				break;
			
			case ShaderDataType::Float3:
				material->GetShader()->UploadFloat3(nameofuniform, *(glm::vec3*)addressofvalue);
				break;
			case ShaderDataType::Float4:
				material->GetShader()->UploadFloat4(nameofuniform, *(glm::vec4*)addressofvalue);
				break;
			case ShaderDataType::Mat4:
				material->GetShader()->UploadMat4(nameofuniform, *(glm::mat4*)addressofvalue);
				break;
			}
		}
		//Apply Material Uniforms

		//Bind Geometry(VAO and IBO)

		//Submit Draw Call
	}

	void Renderer3D::end() {
		data->scenewideuniforms.clear();
	}
}