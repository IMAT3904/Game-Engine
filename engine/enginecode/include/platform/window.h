#pragma once
#include "core/events/EventHandler.h"
#include "rendering/graphicsContext.h"

/** \file window.h
*/

namespace Engine {
	/** \class WindowProperties
** \brief A class to hold the data for the window


**/
	struct WindowProperties {
		char* title; //!< The title of the window
		unsigned int width; //!< The width of the window
		unsigned int height; //!< The height of the window
		bool isfullscreen; //!< A bool to state is the window is fullscreen or not
		bool isvsync; //!< A bool to state is the window has vsync or not
		WindowProperties(char* title = "Window", unsigned int width = 800, unsigned int height = 600, bool isfullscreen = false) : title(title), width(width), height(height), isfullscreen(isfullscreen) {} //!< A constructor to implement the values into an object
	};

	/** \class Window
** \brief a class to create and edit a window


**/
	class Window {
	public:
		virtual void init(const WindowProperties& newprops) = 0; //!< initialise the window
		virtual void close() = 0; //!< close the window
		virtual ~Window() {}; //!< deconstructor
		virtual void onupdate(float timestep) = 0; //!< on every update
		virtual void setvsync(bool vsync) = 0; //!< change vsync
		virtual unsigned int getwidth() const = 0; //!< get the width
		virtual unsigned int getheigth() const = 0; //!< get the height
		virtual void* getnativewindow() const = 0; //!< get the native window
		virtual bool isfullscreen() const = 0; //!< check if fullscreen
		virtual bool isvsync() const = 0; //!< check if vsync is enabled

		virtual EventHandler& gethandler() = 0; //!< get the event handler

		static Window* create(const WindowProperties& newprops = WindowProperties()); //!< an improvised constructor to create a new window with WindowProperties
	protected:
		EventHandler handler; //!< the event handler
		std::shared_ptr<GraphicsContext> m_context; //!< the graphics context
	};
}