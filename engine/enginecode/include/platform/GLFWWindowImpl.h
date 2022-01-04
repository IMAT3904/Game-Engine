#pragma once
#include "window.h"
#include <GLFW/glfw3.h>

/** \file GLFWWindowImpl.h
*/

namespace Engine {
	/** \class GLFWWindowImpl
** \brief a GLFW Window class that uses Window


**/
	class GLFWWindowImpl : public Window {
	public:
		GLFWWindowImpl(const WindowProperties& newprops); //!< Constructor that takes WindowProperties
		virtual void init(const WindowProperties& newprops) override; //!< initialise the window
		virtual void close() override; //!< close the window
		//virtual ~Window() {};
		virtual void onupdate(float timestep) override; //!< on every update
		virtual void setvsync(bool vsync) override; //!< change vsync
		virtual unsigned int getwidth() const override { return props.width; } //!< get the width
		virtual unsigned int getheigth() const override { return props.height; } //!< get the height
		virtual void* getnativewindow() const override { return native; } //!< get the native window
		virtual bool isfullscreen() const override { return props.isfullscreen; } //!< check if fullscreen
		virtual bool isvsync() const override { return props.isvsync; } //!< check if vsync is enabled

		inline EventHandler& gethandler() override { return handler; } //!< get the event handler

	private:
		WindowProperties props; //!< Window properties
		GLFWwindow* native; //!< native window
		float aspectratio; //!< aspect ratio
	};
}