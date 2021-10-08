/** \file application.cpp
*/

#include "engine_pch.h"
#include "core/application.h"

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
	}

	Application::~Application()
	{
		log->stop();
	}


	void Application::run()
	{
		while (m_running)
		{
			Log::info("Hello world! {0} {1}", 42, "I am a string");
		};
	}

}
