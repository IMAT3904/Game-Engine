/** \file application.h
*/
#pragma once

#include "systems/log.h"
#include "events/EventHandler.h"
#include "events/event.h"
#include "events/windowsevent.h"
#include "events/keyboardevent.h"
#include "events/mouseevent.h"
#include "../../include/platform/window.h"
#include "../../include/platform/inputpoller.h"


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
		std::shared_ptr<System> windowsystem;
		std::shared_ptr<Window> window;


	private:
		static Application* s_instance; //!< Singleton instance of the application
		bool m_running = true; //!< Is the application running?
		EventHandler handler;
	public:
		virtual ~Application(); //!< Deconstructor
		inline static Application& getInstance() { return *s_instance; } //!< Instance getter from singleton pattern
		void run(); //!< Main loop
		bool onclose(WindowCloseEvent& e);
		bool onresize(WindowResizeEvent& e);
		bool onmoved(WindowMovedEvent& e);
		bool ongainfocus(WindowFocusEvent& e);
		bool onlostfocus(WindowLostFocusEvent& e);
		bool onkeypressed(KeyPressed& e);
		bool onkeyreleased(KeyReleased& e);
		bool onmousepressed(MouseButtonPressedEvent& e);
		bool onmousereleased(MouseButtonReleasedEvent& e);
		bool onmousewheel(MouseScrolledEvent& e);
		bool onmousemoved(MouseMovedEvent& e);
	};

	// To be defined in users code
	Application* startApplication(); //!< Function definition which provides an entry hook
}