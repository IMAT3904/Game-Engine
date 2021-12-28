#include "engine_pch.h"
#include "rendering/Renderer2D.h"
#include <glad/glad.h>
#include <glm/gtc/matrix_transform.hpp>
namespace Engine {
	std::shared_ptr<Renderer2D::InternalData> Renderer2D::data = nullptr;

	void Renderer2D::init() {
		data.reset(new InternalData);
		unsigned char whitepixel[4] = { 255,255,255,255 };
		data->defaulttexture.reset(Texture::create(1, 1, 4, whitepixel));
		data->defaulttint = { 1.0f,1.0f,1.0f,1.0f };
		data->model = glm::mat4(1.0f);
		data->shader.reset(Shader::create("./assets/shaders/quad.glsl"));

		float vertices[16] = {
			-0.5f,-0.5f,0.0f,0.0f,
			-0.5f,0.5f,0.0f,1.0f,
			0.5f,0.5f,1.0f,1.0f,
			0.5f,-0.5f,1.0f,0.0f
		};

		uint32_t indices[4] = { 0,1,2,3 };

		std::shared_ptr<VertexBuffer> VBO;
		std::shared_ptr<IndexBuffer> IBO;

		data->VAO.reset(VertexArray::create());
		VBO.reset(VertexBuffer::create(vertices, sizeof(vertices), VertexBufferLayout({ ShaderDataType::Float2 , ShaderDataType::Float2 })));
		IBO.reset(IndexBuffer::create(indices, 4));
		data->VAO->AddVertexBuffer(VBO);
		data->VAO->SetIndexBuffer(IBO);
		
		//Font Filepath
		const char* filepath = "./assets/fonts/AGENCYR.TTF";
		//Init FreeType
		if (FT_Init_FreeType(&data->ft)) { Log::error("FreeType could not be initialised"); }
		if (FT_New_Face(data->ft,filepath,0,&data->fontface)) { Log::error("FreeType could not load font: {0}",filepath); }
		int32_t charsize = 86;
		if (FT_Set_Pixel_Sizes(data->fontface, 0, charsize)) { Log::error("FreeType could not set font size: {0}",charsize); }

		data->fonttexture.reset(Texture::create(256, 256, 4, nullptr));
		
	}

	void Renderer2D::begin(const SceneWideUniforms& swu) {
		glUseProgram(data->shader->GetID());
		for (auto& datapair : swu) {
			const char* nameofuniform = datapair.first;
			ShaderDataType sdt = datapair.second.first;
			void* addressofvalue = datapair.second.second;

			switch (sdt) {
			case ShaderDataType::Int:
				data->shader->UploadInt(nameofuniform, *(int*)addressofvalue);
				break;
			case ShaderDataType::Float3:
				data->shader->UploadFloat3(nameofuniform, *(glm::vec3*)addressofvalue);
				break;
			case ShaderDataType::Float4:
				data->shader->UploadFloat4(nameofuniform, *(glm::vec4*)addressofvalue);
				break;
			case ShaderDataType::Mat4:
				data->shader->UploadMat4(nameofuniform, *(glm::mat4*)addressofvalue);
				break;
			}
		}

		glBindVertexArray(data->VAO->GetRenderID());
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, data->VAO->GetIndexBuffer()->GetRenderID());
	}

	void Renderer2D::submit(const Quad& quad, const glm::vec4& tint) {
		Renderer2D::submit(quad, tint, data->defaulttexture);
	}

	void Renderer2D::submit(const Quad& quad, const std::shared_ptr<Texture>& texture) {
		Renderer2D::submit(quad, data->defaulttint, texture);
	}

	void Renderer2D::submit(const Quad& quad, const glm::vec4& tint, float angle, bool degrees) {
		Renderer2D::submit(quad, tint, data->defaulttexture, angle, degrees);
	}

	void Renderer2D::submit(const Quad& quad, const std::shared_ptr<Texture>& texture, float angle, bool degrees) {
		Renderer2D::submit(quad, data->defaulttint,texture, angle, degrees);
	}

	void Renderer2D::submit(const Quad& quad, const glm::vec4& tint, const std::shared_ptr<Texture>& texture) {
		glBindTexture(GL_TEXTURE_2D, texture->getID());
		data->model = glm::scale(glm::translate(glm::mat4(1.0f), quad.translate), quad.scale);

		data->shader->UploadInt("u_texData", 0);
		data->shader->UploadFloat4("u_tint", tint);
		data->shader->UploadMat4("u_model", data->model);
		auto dc = data->VAO->GetDrawCount();

		glBindVertexArray(data->VAO->GetRenderID());
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, data->VAO->GetIndexBuffer()->GetRenderID());

		glDrawElements(GL_QUADS, data->VAO->GetDrawCount(), GL_UNSIGNED_INT, nullptr);
	}

	void Renderer2D::submit(const Quad& quad, const glm::vec4& tint, const std::shared_ptr<Texture>& texture, float angle, bool degrees) {
		if (degrees) angle = glm::radians(angle);

		glBindTexture(GL_TEXTURE_2D, texture->getID());
		data->model = glm::scale(glm::rotate(glm::translate(glm::mat4(1.0f), quad.translate), angle, { 0.0f,0.0f,1.0f }), quad.scale);

		data->shader->UploadInt("u_texData", 0);
		data->shader->UploadFloat4("u_tint", tint);
		data->shader->UploadMat4("u_model", data->model);
		auto dc = data->VAO->GetDrawCount();

		glBindVertexArray(data->VAO->GetRenderID());
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, data->VAO->GetIndexBuffer()->GetRenderID());

		glDrawElements(GL_QUADS, data->VAO->GetDrawCount(), GL_UNSIGNED_INT, nullptr);
	}

	void Renderer2D::submit(char ch, glm::vec2& position, float& advance, const glm::vec4 tint) {
		if (FT_Load_Char(data->fontface, ch, FT_LOAD_RENDER)) {
			Log::error("Could not load glyph for char {0}", ch);
		}
		else {
			//Glyph data
			uint32_t glyphwidth = data->fontface->glyph->bitmap.width;
			uint32_t glyphheight = data->fontface->glyph->bitmap.rows;
			glm::vec2 glyphsize(glyphwidth, glyphheight);
			glm::vec2 glyphbearing(data->fontface->glyph->bitmap_left, -data->fontface->glyph->bitmap_top);

			//Calculate the advance
			advance = static_cast<float>(data->fontface->glyph->advance.x >> 6);

			//Claculate the quad
			glm::vec2 glyphhandextents(data->fonttexture->getWidth() * 0.5f, data->fonttexture->getHeight() * 0.5f);
			glm::vec2 glyphcentre = (position + glyphbearing) + glyphhandextents;
			Quad quad = Quad::CreateCentreHalfExtents(glyphcentre, glyphhandextents);

			//Submit quad
			submit(quad, tint, data->fonttexture);

		}
	}

	void Renderer2D::end() {

	}

	Quad Quad::CreateCentreHalfExtents(const glm::vec2& centre, const glm::vec2& halfextents) {
		Quad result;
		result.translate = glm::vec3(centre, 0.0f);
		result.scale = glm::vec3(halfextents * 2.0f, 1.0f);
		return result;
	}
}