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
		std::shared_ptr<OpenGLTexture> lettertexture;
		lettertexture.reset(new OpenGLTexture("assets/textures/letterAndNumberCube.png"));
		std::shared_ptr<OpenGLTexture> numbertexture;
		//numbertexture.reset(new OpenGLTexture("assets/textures/numberCube.png"));

		SubTexture lettercube(lettertexture, { 0.0f,0.0f }, { 1.0f,0.5f });
		SubTexture numbercube(lettertexture, { 0.f,0.5f }, { 1.0f,1.0f });

#pragma endregion

#pragma region RAW_DATA

			float cubeVertices[8 * 24] = {
				//	 <------ Pos ------>  <--- normal --->  <-- UV -->
					 0.5f,  0.5f, -0.5f,  0.f,  0.f, -1.f,  numbercube.transformU(0.f),   numbercube.transformV(0.f),
					 0.5f, -0.5f, -0.5f,  0.f,  0.f, -1.f,  numbercube.transformU(0.f),   numbercube.transformV(0.5f),
					-0.5f, -0.5f, -0.5f,  0.f,  0.f, -1.f,  numbercube.transformU(0.33f), numbercube.transformV(0.5f),
					-0.5f,  0.5f, -0.5f,  0.f,  0.f, -1.f,  numbercube.transformU(0.33f), numbercube.transformV(0.f),
					-0.5f, -0.5f, 0.5f,   0.f,  0.f,  1.f,  numbercube.transformU(0.33f), numbercube.transformV(0.5f),
					 0.5f, -0.5f, 0.5f,   0.f,  0.f,  1.f,  numbercube.transformU(0.66f), numbercube.transformV(0.5f),
					 0.5f,  0.5f, 0.5f,   0.f,  0.f,  1.f,  numbercube.transformU(0.66f), numbercube.transformV(0.f),
					-0.5f,  0.5f, 0.5f,   0.f,  0.f,  1.f,  numbercube.transformU(0.33),  numbercube.transformV(0.f),
					-0.5f, -0.5f, -0.5f,  0.f, -1.f,  0.f,  numbercube.transformU(1.f),   numbercube.transformV(0.f),
					 0.5f, -0.5f, -0.5f,  0.f, -1.f,  0.f,  numbercube.transformU(0.66f), numbercube.transformV(0.f),
					 0.5f, -0.5f, 0.5f,   0.f, -1.f,  0.f,  numbercube.transformU(0.66f), numbercube.transformV(0.5f),
					-0.5f, -0.5f, 0.5f,   0.f, -1.f,  0.f,  numbercube.transformU(1.0f),  numbercube.transformV(0.5f),
					 0.5f,  0.5f, 0.5f,   0.f,  1.f,  0.f,  numbercube.transformU(0.f),   numbercube.transformV(0.5f),
					 0.5f,  0.5f, -0.5f,  0.f,  1.f,  0.f,  numbercube.transformU(0.f),   numbercube.transformV(1.0f),
					-0.5f,  0.5f, -0.5f,  0.f,  1.f,  0.f,  numbercube.transformU(0.33f), numbercube.transformV(1.0f),
					-0.5f,  0.5f, 0.5f,   0.f,  1.f,  0.f,  numbercube.transformU(0.3f),  numbercube.transformV(0.5f),
					-0.5f,  0.5f, 0.5f,  -1.f,  0.f,  0.f,  numbercube.transformU(0.66f), numbercube.transformV(0.5f),
					-0.5f,  0.5f, -0.5f, -1.f,  0.f,  0.f,  numbercube.transformU(0.33f), numbercube.transformV(0.5f),
					-0.5f, -0.5f, -0.5f, -1.f,  0.f,  0.f,  numbercube.transformU(0.33f), numbercube.transformV(1.0f),
					-0.5f, -0.5f, 0.5f,  -1.f,  0.f,  0.f,  numbercube.transformU(0.66f), numbercube.transformV(1.0f),
					 0.5f, -0.5f, -0.5f,  1.f,  0.f,  0.f,  numbercube.transformU(1.0f),  numbercube.transformV(1.0f),
					 0.5f,  0.5f, -0.5f,  1.f,  0.f,  0.f,  numbercube.transformU(1.0f),  numbercube.transformV(0.5f),
					 0.5f,  0.5f, 0.5f,   1.f,  0.f,  0.f,  numbercube.transformU(0.66f), numbercube.transformV(0.5f),
					 0.5f, -0.5f, 0.5f,   1.f,  0.f,  0.f,  numbercube.transformU(0.66f), numbercube.transformV(1.0f)
			};

			float pyramidVertices[6 * 16] = {
				//	 <------ Pos ------>  <--- colour ---> 
					-0.5f, -0.5f, -0.5f,  0.8f, 0.2f, 0.8f, //  square Magneta
					 0.5f, -0.5f, -0.5f,  0.8f, 0.2f, 0.8f,
					 0.5f, -0.5f,  0.5f,  0.8f, 0.2f, 0.8f,
					-0.5f, -0.5f,  0.5f,  0.8f, 0.2f, 0.8f,

					-0.5f, -0.5f, -0.5f,  0.2f, 0.8f, 0.2f,  //triangle Green
					-0.5f, -0.5f,  0.5f,  0.2f, 0.8f, 0.2f,
					 0.0f,  0.5f,  0.0f,  0.2f, 0.8f, 0.2f,

					-0.5f, -0.5f,  0.5f,  1.0f, 0.0f, 0.f, //triangle Red
					 0.5f, -0.5f,  0.5f,  1.0f, 0.0f, 0.f,
					 0.0f,  0.5f,  0.0f,  1.0f, 0.0f, 0.f,

					 0.5f, -0.5f,  0.5f,  0.8f, 0.8f, 0.2f, //  triangle Yellow
					 0.5f, -0.5f, -0.5f,  0.8f, 0.8f, 0.2f,
					 0.0f,  0.5f,  0.0f,  0.8f, 0.8f, 0.2f,

					 0.5f, -0.5f, -0.5f,  0.f, 0.2f, 1.0f,//  triangle Blue
					-0.5f, -0.5f, -0.5f,  0.f, 0.2f, 1.0f,
					 0.0f,  0.5f,  0.0f,  0.f, 0.2f, 1.0f
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
			/*uint32_t cubeVAO, cubeVBO, cubeIBO;

			glCreateVertexArrays(1, &cubeVAO);
			glBindVertexArray(cubeVAO);

			glCreateBuffers(1, &cubeVBO);
			glBindBuffer(GL_ARRAY_BUFFER, cubeVBO);
			glBufferData(GL_ARRAY_BUFFER, sizeof(cubeVertices), cubeVertices, GL_STATIC_DRAW);

			glCreateBuffers(1, &cubeIBO);
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, cubeIBO);
			glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(cubeIndices), cubeIndices, GL_STATIC_DRAW);

			glEnableVertexAttribArray(0);
			glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0); // position
			glEnableVertexAttribArray(1);
			glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float))); // Normal
			glEnableVertexAttribArray(2);
			glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float))); // UV co-ords*/

			std::shared_ptr<VertexArray> cubeVAO;
			std::shared_ptr<VertexBuffer> cubeVBO;
			std::shared_ptr<IndexBuffer> cubeIBO;

			cubeVAO.reset(VertexArray::create());

			BufferLayout cubeBL = { ShaderDataType::Float3,ShaderDataType::Float3,ShaderDataType::Float2 };
			cubeVBO.reset(VertexBuffer::create(cubeVertices,sizeof(cubeVertices),cubeBL));

			cubeIBO.reset(IndexBuffer::create(cubeIndices,36));

			cubeVAO->AddVertexBuffer(cubeVBO);
			cubeVAO->SetIndexBuffer(cubeIBO);

			std::shared_ptr<VertexArray> pyramidVAO;
			std::shared_ptr<VertexBuffer> pyramidVBO;
			std::shared_ptr<IndexBuffer> pyramidIBO;

			pyramidVAO.reset(VertexArray::create());
			BufferLayout pyramidBL = { ShaderDataType::Float3,ShaderDataType::Float3 };
			pyramidVBO.reset(VertexBuffer::create(pyramidVertices, sizeof(pyramidVertices), pyramidBL));
			pyramidIBO.reset(IndexBuffer::create(pyramidIndices, 18));

			pyramidVAO->AddVertexBuffer(pyramidVBO);
			pyramidVAO->SetIndexBuffer(pyramidIBO);			
#pragma endregion


#pragma region SHADERS
			std::shared_ptr<Shader> FCShader;
			FCShader.reset(Shader::create("./assets/shaders/flatcolour.glsl"));

			std::shared_ptr<Shader> TPShader;
			TPShader.reset(Shader::create("./assets/shaders/texturedphong.glsl"));

			
#pragma endregion 

		glm::mat4 view = glm::lookAt(
			glm::vec3(0.f, 0.f, 0.f),
			glm::vec3(0.f, 0.f, -1.f),
			glm::vec3(0.f, 1.f, 0.f)
		);
		glm::mat4 projection = glm::perspective(glm::radians(45.f), 1024.f / 800.f, 0.1f, 100.f);

		glm::mat4 models[3];
		models[0] = glm::translate(glm::mat4(1.0f), glm::vec3(-2.f, 0.f, -6.f));
		models[1] = glm::translate(glm::mat4(1.0f), glm::vec3(0.f, 0.f, -6.f));
		models[2] = glm::translate(glm::mat4(1.0f), glm::vec3(2.f, 0.f, -6.f));

		glEnable(GL_DEPTH_TEST);
		glClearColor(1.0f, 0.0f, 1.0f, 1.0f);
		while (m_running)
		{
			timestep = timer->getelapsedtime();
			timer->reset();
			//Log::trace("FPS {0}", 1.0f / timestep);

			if (InputPoller::iskeypressed(NG_KEY_W)) Log::error("W Pressed");
			if (InputPoller::ismousebuttonpressed(NG_MOUSE_BUTTON_1)) Log::error("Left Mouse Button Pressed");
			//Log::trace("Current mouse pos: ({0}, {1})", InputPoller::getmousex(), InputPoller::getmousey());

			for (auto& model : models) { model = glm::rotate(model, timestep, glm::vec3(0.f, 1.0, 0.f)); }

			// Do frame stuff
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
			GLuint uniformLocation;
			glUseProgram(FCShader->GetID());

			glBindVertexArray(pyramidVAO->GetRenderID());
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, pyramidIBO->GetRenderID());

			

			uniformLocation = glGetUniformLocation(FCShader->GetID(), "u_model");
			glUniformMatrix4fv(uniformLocation, 1, GL_FALSE, glm::value_ptr(models[0])); // Must include <glm/gtc/type_ptr.hpp>

			uniformLocation = glGetUniformLocation(FCShader->GetID(), "u_view");
			glUniformMatrix4fv(uniformLocation, 1, GL_FALSE, glm::value_ptr(view));

			uniformLocation = glGetUniformLocation(FCShader->GetID(), "u_projection");
			glUniformMatrix4fv(uniformLocation, 1, GL_FALSE, glm::value_ptr(projection));

			glDrawElements(GL_TRIANGLES, 3 * 6, GL_UNSIGNED_INT, nullptr);
			
			glUseProgram(TPShader->GetID());
			

			glBindVertexArray(cubeVAO->GetRenderID());
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, cubeIBO->GetRenderID());


			uniformLocation = glGetUniformLocation(TPShader->GetID(), "u_model");
			glUniformMatrix4fv(uniformLocation, 1, GL_FALSE, glm::value_ptr(models[1]));

			uniformLocation = glGetUniformLocation(TPShader->GetID(), "u_view");
			glUniformMatrix4fv(uniformLocation, 1, GL_FALSE, glm::value_ptr(view));

			uniformLocation = glGetUniformLocation(TPShader->GetID(), "u_projection");
			glUniformMatrix4fv(uniformLocation, 1, GL_FALSE, glm::value_ptr(projection));

			uniformLocation = glGetUniformLocation(TPShader->GetID(), "u_lightColour");
			glUniform3f(uniformLocation, 1.f, 1.f, 1.f);

			uniformLocation = glGetUniformLocation(TPShader->GetID(), "u_lightPos");
			glUniform3f(uniformLocation, 1.f, 4.f, 6.f);

			uniformLocation = glGetUniformLocation(TPShader->GetID(), "u_viewPos");
			glUniform3f(uniformLocation, 0.f, 0.f, 0.f);

			glBindTexture(GL_TEXTURE_2D, lettertexture->getID());
			uniformLocation = glGetUniformLocation(TPShader->GetID(), "u_texData");
			glUniform1i(uniformLocation, 0);

			glDrawElements(GL_TRIANGLES, cubeVAO->GetDrawCount(), GL_UNSIGNED_INT, nullptr);

			uniformLocation = glGetUniformLocation(TPShader->GetID(), "u_model");
			glUniformMatrix4fv(uniformLocation, 1, GL_FALSE, glm::value_ptr(models[2]));

			//glBindTexture(GL_TEXTURE_2D, numbertexture->getID());

			glDrawElements(GL_TRIANGLES, cubeVAO->GetDrawCount(), GL_UNSIGNED_INT, nullptr);


			if (InputPoller::iskeypressed(NG_KEY_W)) Log::error("W Pressed");
			if (InputPoller::ismousebuttonpressed(NG_MOUSE_BUTTON_1)) Log::error("Mouse left");
			//Log::file("Hello world! {0} {1}", 42, "I am a string");
			window->onupdate(timestep);
		}
	};
}
