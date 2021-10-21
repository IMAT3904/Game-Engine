/** \file application.h
*/
#pragma once

#include "systems/log.h"
#include "events/EventHandler.h"
#include "events/event.h"


namespace Engine {

	/**
	\class Application
	Fundemental class of the engine. A singleton which runs the game loop infinitely.
	Provides ...
	*/

	class Application
	{
	protected:
		Application(); //!< Constructor

		std::shared_ptr<Log> log;
	private:
		static Application* s_instance; //!< Singleton instance of the application
		bool m_running = true; //!< Is the application running?
		EventHandler handler;

		bool onclose(WindowCloseEvent& c);
	public:
		virtual ~Application(); //!< Deconstructor
		inline static Application& getInstance() { return *s_instance; } //!< Instance getter from singleton pattern
		void run(); //!< Main loop
		
	};

	// To be defined in users code
	Application* startApplication(); //!< Function definition which provides an entry hook
}