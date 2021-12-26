/** \file application.cpp
*/

#include "engine_pch.h"
#include <glad/glad.h>

#include "core/application.h"
#include "platform/wintimer.h"

#ifdef NG_PLATFORM_WINDOWS
#include "include/platform/GLFWSystem.h"
#endif

#include "stb_image.h"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "rendering/OpenGLVertexArray.h"

#include "rendering/OpenGLShader.h"
#include "rendering/OpenGLTexture.h"
#include "rendering/SubTexture.h"
#include "rendering/IndexBuffer.h"
#include "rendering/VertexBuffer.h"
#include "rendering/Shader.h"
#include "rendering/Texture.h"
#include "rendering/OpenGLUniformBuffer.h"
#include "rendering/UniformBuffer.h"

#include "rendering/Renderer3D.h"
#include "rendering/Renderer2D.h"



namespace Engine {
	// Set static vars
	Application* Application::s_instance = nullptr;

	Application::Application()
	{
		if (s_instance == nullptr)
		{
			s_instance = this;
		}

		//Start
		log.reset(new Log);
		log->start();

		timer.reset(new WinTimer);
		timer->start();
		

		windowsystem.reset(new GLFWSystem);
		windowsystem->start();

		WindowProperties props("My Engine", 1024, 768);
		window.reset(Window::create(props));

		window->gethandler().setonclosecallback(std::bind(&Application::onclose, this, std::placeholders::_1));
		window->gethandler().setonresizecallback(std::bind(&Application::onresize, this, std::placeholders::_1));
		window->gethandler().setonmovedcallback(std::bind(&Application::onmoved, this, std::placeholders::_1));
		window->gethandler().setonfocuscallback(std::bind(&Application::ongainfocus, this, std::placeholders::_1));
		window->gethandler().setonlostfocuscallback(std::bind(&Application::onlostfocus, this, std::placeholders::_1));
		window->gethandler().setonkeypressedcallback(std::bind(&Application::onkeypressed, this, std::placeholders::_1));
		window->gethandler().setonkeyreleasedcallback(std::bind(&Application::onkeyreleased, this, std::placeholders::_1));
		window->gethandler().setonmousepressedcallback(std::bind(&Application::onmousepressed, this, std::placeholders::_1));
		window->gethandler().setonmousereleasedcallback(std::bind(&Application::onmousereleased, this, std::placeholders::_1));
		window->gethandler().setonmousemovedcallback(std::bind(&Application::onmousemoved, this, std::placeholders::_1));
		InputPoller::setcurrentwindow(window->getnativewindow());
	}

	bool Application::onclose(WindowCloseEvent& e) {
		e.handle(true);
		m_running = false;
		return e.handled();
	}

	bool Application::onresize(WindowResizeEvent& e){
		e.handle(true);
		auto& size = e.getsize();
		Log::info("Window Resize: ({0}, {1})", size.x, size.y);
		auto& pos = e.getsize();
		return e.handled();
	}

	bool Application::onmoved(WindowMovedEvent& e){
		e.handle(true);
		auto& pos = e.getpos();
		return e.handled();
	}

	bool Application::ongainfocus(WindowFocusEvent& e){
		e.handle(true);
		return e.handled();
	}

	bool Application::onlostfocus(WindowLostFocusEvent& e){
		e.handle(true);
		return e.handled();
	}

	bool Application::onkeypressed(KeyPressed& e){
		e.handle(true);
		//Log::trace("Key Pressed: Key: {0}", e.getkeycode());
		//if (e.getkeycode() == NG_KEY_SPACE) Log::error("SPACEBAR");
		return e.handled();
	}

	bool Application::onkeyreleased(KeyReleased& e){
		e.handle(true);
		//if (e.getkeycode() == NG_KEY_UP) Log::error("UP");
		return e.handled();
	}

	bool Application::onmousepressed(MouseButtonPressedEvent& e){
		e.handle(true);
		//if (e.getbutton() == NG_MOUSE_BUTTON_1) Log::error("LEFT");
		return e.handled();
	}

	bool Application::onmousereleased(MouseButtonReleasedEvent& e){
		e.handle(true);
		//if (e.getbutton() == NG_MOUSE_BUTTON_2) Log::error("RIGHT");
		return e.handled();
	}

	bool Application::onmousewheel(MouseScrolledEvent& e){
		e.handle(true);
		return e.handled();
	}

	bool Application::onmousemoved(MouseMovedEvent& e){
		e.handle(true);
		auto& pos = e.getpos();
		return e.handled();
	}


	Application::~Application()
	{
		log->stop();
	}


	void Application::run()
	{
		float timestep = 0;

#pragma region TEXTURES
		std::shared_ptr<Texture> lettertexture;
		lettertexture.reset(Texture::create("assets/textures/letterCube.png"));
		std::shared_ptr<Texture> numbertexture;
		numbertexture.reset(Texture::create("assets/textures/numberCube.png"));
		unsigned char whitepixel[4] = { 255,255,255,255 };
		std::shared_ptr<Texture> plainwhitetexture;
		plainwhitetexture.reset(Texture::create(1, 1, 4, whitepixel));

#pragma endregion

#pragma region RAW_DATA

		float cubeVertices[8 * 24] = {
			//	 <------ Pos ------>  <--- normal --->  <-- UV -->
				 0.5f,  0.5f, -0.5f,  0.f,  0.f, -1.f,  0.0f, 0.0f,
				 0.5f, -0.5f, -0.5f,  0.f,  0.f, -1.f,  0.0f, 0.5f,
				-0.5f, -0.5f, -0.5f,  0.f,  0.f, -1.f,  0.33f, 0.5f,
				-0.5f,  0.5f, -0.5f,  0.f,  0.f, -1.f,  0.33f, 0.0f,

				-0.5f, -0.5f, 0.5f,   0.f,  0.f,  1.f,  0.33f, 0.5f,
				 0.5f, -0.5f, 0.5f,   0.f,  0.f,  1.f,  0.66f, 0.5f,
				 0.5f,  0.5f, 0.5f,   0.f,  0.f,  1.f,  0.66f, 0.0f,
				-0.5f,  0.5f, 0.5f,   0.f,  0.f,  1.f,  0.33f, 0.0f,

				-0.5f, -0.5f, -0.5f,  0.f, -1.f,  0.f,  1.0f, 0.0f,
				 0.5f, -0.5f, -0.5f,  0.f, -1.f,  0.f,  0.66f, 0.0f,
				 0.5f, -0.5f, 0.5f,   0.f, -1.f,  0.f,  0.66f, 0.5f,
				-0.5f, -0.5f, 0.5f,   0.f, -1.f,  0.f,  1.0f, 0.5f,

				 0.5f,  0.5f, 0.5f,   0.f,  1.f,  0.f,  0.0f, 0.5f,
				 0.5f,  0.5f, -0.5f,  0.f,  1.f,  0.f,  0.0f, 1.0f,
				-0.5f,  0.5f, -0.5f,  0.f,  1.f,  0.f,  0.33f, 1.0f,
				-0.5f,  0.5f, 0.5f,   0.f,  1.f,  0.f,  0.3f, 0.5f,

				-0.5f,  0.5f, 0.5f,  -1.f,  0.f,  0.f,  0.66f, 0.5f,
				-0.5f,  0.5f, -0.5f, -1.f,  0.f,  0.f,  0.33f, 0.5f,
				-0.5f, -0.5f, -0.5f, -1.f,  0.f,  0.f,  0.33f, 1.0f,
				-0.5f, -0.5f, 0.5f,  -1.f,  0.f,  0.f,  0.66f, 1.0f,

				 0.5f, -0.5f, -0.5f,  1.f,  0.f,  0.f,  1.0f, 1.0f,
				 0.5f,  0.5f, -0.5f,  1.f,  0.f,  0.f,  1.0f, 0.5f,
				 0.5f,  0.5f, 0.5f,   1.f,  0.f,  0.f,  0.66f, 0.5f,
				 0.5f, -0.5f, 0.5f,   1.f,  0.f,  0.f,  0.66f, 1.0f
		};

		float pyramidVertices[8 * 16] = {
			//	 <------ Pos ------>  <--- normal --->  <--- UV ---> 
				-0.5f, -0.5f, -0.5f,  0.f, -1.f, 0.f,			0.0f, 0.0f, //  square Magneta
				 0.5f, -0.5f, -0.5f,  0.f, -1.f, 0.f,			0.0f, 0.5f,
				 0.5f, -0.5f,  0.5f,  0.f, -1.f, 0.f,			0.33f, 0.5f,
				-0.5f, -0.5f,  0.5f,  0.f, -1.f, 0.f,			0.33f, 0.0f,

				-0.5f, -0.5f, -0.5f,  -0.8944f, 0.4472f, 0.f,	0.33f, 0.5f,  //triangle Green
				-0.5f, -0.5f,  0.5f,  -0.8944f, 0.4472f, 0.f,	0.66, 0.5f,
				 0.0f,  0.5f,  0.0f,  -0.8944f, 0.4472f, 0.f,	(0.33f + 0.66f) * 0.5f, 0.0f,

				-0.5f, -0.5f,  0.5f,  0.f, 0.4472f, 0.8944f,	0.0f, 0.0f, //triangle Red
				 0.5f, -0.5f,  0.5f,  0.f, 0.4472f, 0.8944f,	0.0f, 0.0f,
				 0.0f,  0.5f,  0.0f,  0.f, 0.4472f, 0.8944f,	0.0f, 0.0f,

				 0.5f, -0.5f,  0.5f,  0.8944f, 0.4472f, 0.f,	0.0f, 0.0f, //  triangle Yellow
				 0.5f, -0.5f, -0.5f,  0.8944f, 0.4472f, 0.f,	0.0f, 0.0f,
				 0.0f,  0.5f,  0.0f,  0.8944f, 0.4472f, 0.f,	0.0f, 0.0f,

				 0.5f, -0.5f, -0.5f,  0.f, 0.4472f, -0.8944f,	0.0f, 0.0f,//  triangle Blue
				-0.5f, -0.5f, -0.5f,  0.f, 0.4472f, -0.8944f,	0.0f, 0.0f,
				 0.0f,  0.5f,  0.0f,  0.f, 0.4472f, -0.8944f,	0.0f, 0.0f
		};

		uint32_t pyramidIndices[3 * 6] =
		{
			0, 1, 2,
			2, 3, 0,
			4, 5, 6,
			7, 8, 9,
			10, 11, 12,
			13, 14, 15
		};

		uint32_t cubeIndices[3 * 12] = {
			0, 1, 2,
			2, 3, 0,
			4, 5, 6,
			6, 7, 4,
			8, 9, 10,
			10, 11, 8,
			12, 13, 14,
			14, 15, 12,
			16, 17, 18,
			18, 19, 16,
			20, 21, 22,
			22, 23, 20
		};
#pragma endregion

#pragma region GL_BUFFERS
		std::shared_ptr<VertexArray> cubeVAO;
		std::shared_ptr<VertexBuffer> cubeVBO;
		std::shared_ptr<IndexBuffer> cubeIBO;

		cubeVAO.reset(VertexArray::create());

		VertexBufferLayout cubeBL = { ShaderDataType::Float3,ShaderDataType::Float3,ShaderDataType::Float2 };
		cubeVBO.reset(VertexBuffer::create(cubeVertices, sizeof(cubeVertices), cubeBL));

		cubeIBO.reset(IndexBuffer::create(cubeIndices, 36));

		cubeVAO->AddVertexBuffer(cubeVBO);
		cubeVAO->SetIndexBuffer(cubeIBO);

		std::shared_ptr<VertexArray> pyramidVAO;
		std::shared_ptr<VertexBuffer> pyramidVBO;
		std::shared_ptr<IndexBuffer> pyramidIBO;

		pyramidVAO.reset(VertexArray::create());
		pyramidVBO.reset(VertexBuffer::create(pyramidVertices, sizeof(pyramidVertices), cubeBL));
		pyramidIBO.reset(IndexBuffer::create(pyramidIndices, 18));

		pyramidVAO->AddVertexBuffer(pyramidVBO);
		pyramidVAO->SetIndexBuffer(pyramidIBO);
#pragma endregion


#pragma region SHADERS
		std::shared_ptr<Shader> FCShader;
		FCShader.reset(Shader::create("./assets/shaders/flatcolour.glsl"));

		std::shared_ptr<Shader> TPShader;
		TPShader.reset(Shader::create("./assets/shaders/texturedphong.glsl"));

		std::shared_ptr<Shader> QuadShader;
		QuadShader.reset(Shader::create("./assets/shaders/quad.glsl"));


#pragma endregion 

#pragma region MATERIALS
		std::shared_ptr<Material> pyramidmat;
		std::shared_ptr<Material> lettermat;
		std::shared_ptr<Material> numbermat;

		pyramidmat.reset(new Material(TPShader, { 0.4f,0.7f,0.3f,1.0f }));
		lettermat.reset(new Material(TPShader, lettertexture));
		numbermat.reset(new Material(TPShader, numbertexture));


#pragma endregion

		glm::mat4 view = glm::lookAt(
			glm::vec3(0.f, 0.f, 0.f),
			glm::vec3(0.f, 0.f, -1.f),
			glm::vec3(0.f, 1.f, 0.f)
		);
		glm::mat4 projection = glm::perspective(glm::radians(45.f), 1024.f / 800.f, 0.1f, 100.f);

		//Camera UBO
		uint32_t blocknumber = 0;

		UniformBufferLayout cameralayout = { {"u_projection",ShaderDataType::Mat4},{"u_view",ShaderDataType::Mat4} };

		std::shared_ptr<UniformBuffer> cameraUBO;
		cameraUBO.reset(UniformBuffer::create(cameralayout));
		cameraUBO->AttachShaderBlock(FCShader, "b_camera");
		cameraUBO->AttachShaderBlock(TPShader, "b_camera");

		cameraUBO->UploadData("u_projection", glm::value_ptr(projection));
		cameraUBO->UploadData("u_view", glm::value_ptr(view));

		blocknumber++;
		glm::vec3 lightcolour(1.0f, 1.0f, 1.0f);
		glm::vec3 lightpos(1.0f, 4.0f, 6.0f);
		glm::vec3 viewpos(0.0f, 0.0f, 0.0f);

		uint32_t lightsUBO;
		uint32_t lightsdatasize = sizeof(glm::vec4) * 3;

		glGenBuffers(1, &lightsUBO);
		glBindBuffer(GL_UNIFORM_BUFFER, lightsUBO);
		glBufferData(GL_UNIFORM_BUFFER, lightsdatasize, nullptr, GL_DYNAMIC_DRAW);
		glBindBufferRange(GL_UNIFORM_BUFFER, blocknumber, lightsUBO, 0, lightsdatasize);

		uint32_t blockindex = glGetUniformBlockIndex(TPShader->GetID(), "b_lights");
		glUniformBlockBinding(TPShader->GetID(), blockindex, blocknumber);


		glBufferSubData(GL_UNIFORM_BUFFER, 0, sizeof(glm::vec3), glm::value_ptr(lightpos));
		glBufferSubData(GL_UNIFORM_BUFFER, sizeof(glm::vec4), sizeof(glm::vec3), glm::value_ptr(viewpos));
		glBufferSubData(GL_UNIFORM_BUFFER, sizeof(glm::vec4) * 2, sizeof(glm::vec3), glm::value_ptr(lightcolour));



		glm::mat4 models[3];
		models[0] = glm::translate(glm::mat4(1.0f), glm::vec3(-2.f, 0.f, -6.f));
		models[1] = glm::translate(glm::mat4(1.0f), glm::vec3(0.f, 0.f, -6.f));
		models[2] = glm::translate(glm::mat4(1.0f), glm::vec3(2.f, 0.f, -6.f));

		glm::mat4 view2D = glm::mat4(1.0f);
		glm::mat4 projection2D = glm::ortho(0.0f, static_cast<float>(window->getwidth()), static_cast<float>(window->getheigth()),0.0f);

		glm::vec3 lightdata[3] = { { 1.0f, 1.0f, 1.0f },{1.0f, 4.0f, 6.0f},{0.0f, 0.0f, 0.0f} };
		SceneWideUniforms swu3D;
		swu3D["u_view"] = std::pair<ShaderDataType, void*>(ShaderDataType::Mat4, static_cast<void*>(glm::value_ptr(view)));
		swu3D["u_projection"] = std::pair<ShaderDataType, void*>(ShaderDataType::Mat4, static_cast<void*>(glm::value_ptr(projection)));
		swu3D["u_lightColour"] = std::pair<ShaderDataType, void*>(ShaderDataType::Float3, static_cast<void*>(glm::value_ptr(lightdata[0])));
		swu3D["u_lightPos"] = std::pair<ShaderDataType, void*>(ShaderDataType::Float3, static_cast<void*>(glm::value_ptr(lightdata[1])));
		swu3D["u_viewPos"] = std::pair<ShaderDataType, void*>(ShaderDataType::Float3, static_cast<void*>(glm::value_ptr(lightdata[2])));

		SceneWideUniforms swu2D;
		swu2D["u_view"] = std::pair<ShaderDataType, void*>(ShaderDataType::Mat4, static_cast<void*>(glm::value_ptr(view2D)));
		swu2D["u_projection"] = std::pair<ShaderDataType, void*>(ShaderDataType::Mat4, static_cast<void*>(glm::value_ptr(projection2D)));

		Quad q1 = Quad::CreateCentreHalfExtents({ 400.0f,200.0f }, { 100.0f,50.0f });

		glClearColor(1.0f, 0.0f, 1.0f, 1.0f);
		Renderer3D::init();
		Renderer2D::init();
		while (m_running)
		{
			timestep = timer->getelapsedtime();
			timer->reset();
			//Log::trace("FPS {0}", 1.0f / timestep);

			if (InputPoller::iskeypressed(NG_KEY_W)) Log::error("W Pressed");
			if (InputPoller::ismousebuttonpressed(NG_MOUSE_BUTTON_1)) Log::error("Left Mouse Button Pressed");
			//Log::trace("Current mouse pos: ({0}, {1})", InputPoller::getmousex(), InputPoller::getmousey());

			for (auto& model : models) { model = glm::rotate(model, timestep, glm::vec3(0.f, 1.0, 0.f)); }

			glEnable(GL_DEPTH_TEST);
			Renderer3D::begin(swu3D);
			Renderer3D::submit(pyramidVAO, pyramidmat, models[0]);
			Renderer3D::submit(cubeVAO, lettermat, models[1]);
			Renderer3D::submit(cubeVAO, numbermat, models[2]);
			Renderer3D::end();

			glDisable(GL_DEPTH_TEST);
			Renderer2D::begin(swu2D);
			Renderer2D::submit(q1, { 0.0f,0.0f,1.0f,1.0f });
			Renderer2D::end();


			// Do frame stuff
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
			GLuint uniformLocation;
			glUseProgram(TPShader->GetID());
			glBindTexture(GL_TEXTURE_2D, plainwhitetexture->getID());
			glBindVertexArray(pyramidVAO->GetRenderID());
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, pyramidIBO->GetRenderID());

			
			TPShader->UploadMat4("u_model", models[0]);
			TPShader->UploadFloat4("u_tint", { 0.4f,0.7f,0.3f,1.0f });
			TPShader->UploadInt("u_texData", 0);

			glDrawElements(GL_TRIANGLES, 3 * 6, GL_UNSIGNED_INT, nullptr);			
			
			glBindVertexArray(cubeVAO->GetRenderID());
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, cubeIBO->GetRenderID());

			TPShader->UploadMat4("u_model", models[1]);
			TPShader->UploadFloat4("u_tint", { 1.0f,1.0f,1.0f,1.0f });
			TPShader->UploadInt("u_texData", 0);

			glBindTexture(GL_TEXTURE_2D, lettertexture->getID());
			glDrawElements(GL_TRIANGLES, cubeVAO->GetDrawCount(), GL_UNSIGNED_INT, nullptr);

			TPShader->UploadMat4("u_model", models[2]);

			glBindTexture(GL_TEXTURE_2D, numbertexture->getID());

			glDrawElements(GL_TRIANGLES, cubeVAO->GetDrawCount(), GL_UNSIGNED_INT, nullptr);


			if (InputPoller::iskeypressed(NG_KEY_W)) Log::error("W Pressed");
			if (InputPoller::ismousebuttonpressed(NG_MOUSE_BUTTON_1)) Log::error("Mouse left");
			//Log::file("Hello world! {0} {1}", 42, "I am a string");
			window->onupdate(timestep);
		}
	};
}
