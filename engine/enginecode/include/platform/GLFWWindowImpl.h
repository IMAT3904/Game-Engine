#pragma once
#include "window.h"
#include <GLFW/glfw3.h>

namespace Engine {
	class GLFWWindowImpl : public Window {
	public:
		GLFWWindowImpl(const WindowProperties& newprops);
		virtual void init(const WindowProperties& newprops) override;
		virtual void close() override;
		//virtual ~Window() {};
		virtual void onupdate(float timestep) override;
		virtual void setvsync(bool vsync) override;
		virtual unsigned int getwidth() const override { return props.width; }
		virtual unsigned int getheigth() const override { return props.height; }
		virtual void* getnativewindow() const override { return native; }
		virtual bool isfullscreen() const override { return props.isfullscreen; }
		virtual bool isvsync() const override { return props.isvsync; }

		inline EventHandler& gethandler() override { return handler; }

	private:
		WindowProperties props;
		GLFWwindow* native;
		float aspectratio;
	};
}