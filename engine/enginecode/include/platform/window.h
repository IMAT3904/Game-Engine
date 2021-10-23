#pragma once
#include "core/events/EventHandler.h"
namespace Engine {
	struct WindowProperties {
		char* title;
		unsigned int width;
		unsigned int height;
		bool isfullscreen;
		bool isvsync;
		WindowProperties(char* title = "Window", unsigned int width = 800, unsigned int height = 600, bool isfullscreen = false) : title(title), width(width), height(height), isfullscreen(isfullscreen) {}
	};

	class Window {
	public:
		virtual void init(const WindowProperties& newprops) = 0;
		virtual void close() = 0;
		virtual ~Window() {};
		virtual void onupdate(float timestep) = 0;
		virtual void setvsync(bool vsync) = 0;
		virtual unsigned int getwidth() const = 0;
		virtual unsigned int getheigth() const = 0;
		virtual void* getnativewindow() const = 0;
		virtual bool isfullscreen() const = 0;
		virtual bool isvsync() const = 0;

		virtual EventHandler& gethandler() = 0;

		static Window* create(const WindowProperties& newprops = WindowProperties());
	protected:
		EventHandler handler;
	};
}