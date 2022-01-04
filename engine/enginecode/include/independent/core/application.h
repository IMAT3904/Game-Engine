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
#include "include/independent/systems/timer.h"


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
		std::shared_ptr<Timer> timer;
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
		bool onclose(WindowCloseEvent& e); //!< the on close function
		bool onresize(WindowResizeEvent& e); //!< the on resize function
		bool onmoved(WindowMovedEvent& e); //!< the on moved function
		bool ongainfocus(WindowFocusEvent& e); //!< the on gain focus function
		bool onlostfocus(WindowLostFocusEvent& e); //!< the on lost focus function
		bool onkeypressed(KeyPressed& e); //!< the on key pressed function
		bool onkeyreleased(KeyReleased& e); //!< the on key released function
		bool onmousepressed(MouseButtonPressedEvent& e); //!< the on mouse pressed function
		bool onmousereleased(MouseButtonReleasedEvent& e); //!< the on mouse released function
		bool onmousewheel(MouseScrolledEvent& e); //!< the on mouse wheel function
		bool onmousemoved(MouseMovedEvent& e); //!< the on mouse moved function

		inline std::shared_ptr<Window>& getwindow() { return window; } //!< returns the current window
	};

	// To be defined in users code
	Application* startApplication(); //!< Function definition which provides an entry hook
}