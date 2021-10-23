/** \file application.cpp
*/

#include "engine_pch.h"
#include "core/application.h"
#ifdef NG_PLATFORM_WINDOWS
#include "platform/GLFWSystem.h"
#endif // NG_PLATFORM_WINDOWS


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

		windowsystem.reset(new GLFWSystem);
		windowsystem->start();

		WindowProperties props("My Engine", 1024, 768);
		Window::create(props);

		window->gethandler().setonclosecallback(std::bind(&Application::onclose, this, std::placeholders::_1));
	}

	Application::~Application()
	{
		log->stop();
	}


	void Application::run()
	{
		while (m_running)
		{
			Log::file("Hello world! {0} {1}", 42, "I am a string");
		};
	}

	bool Application::onclose(WindowsCloseEvent& e) {
		e.handle(true);
		m_running = false;
		return e.handled();
	}
}
