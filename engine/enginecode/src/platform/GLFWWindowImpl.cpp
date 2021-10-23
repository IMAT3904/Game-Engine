#pragma once
#include "..\..\include\platform\GLFWWindowImpl.h"
#include "engine_pch.h"
#include "systems/log.h"

namespace Engine {
#ifdef NG_PLATFORM_WINDOWS
	Window* Window::create(const WindowProperties& newprops = WindowProperties()) {
		return new GLFWWindowImpl(newprops);
	}
#endif

	GLFWWindowImpl::GLFWWindowImpl(const WindowProperties& newprops) {
		init(newprops);
	}

	void GLFWWindowImpl::init(const WindowProperties& newprops) {
		props = newprops;
		aspectratio = static_cast<float>(props.width) / static_cast<float>(props.height);

		if (props.isfullscreen) {
			Log::error("fullscreen enabled");
			native = glfwCreateWindow(props.width, props.height, props.title, glfwGetPrimaryMonitor(), nullptr);
		}
		else {
			native = glfwCreateWindow(props.width, props.height, props.title, nullptr, nullptr);
		}
	}

	void GLFWWindowImpl::close(){
		glfwDestroyWindow(native);
	}
	
	void GLFWWindowImpl::onupdate(float timestep) {
		glfwPollEvents();
	}

	void GLFWWindowImpl::setvsync(bool vsync) {
		props.isvsync = vsync;
		if (vsync) {glfwSwapInterval(1);}
		else {glfwSwapInterval(0);}
	}
}
