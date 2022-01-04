#pragma once
#include "engine_pch.h"
#include "platform/GLFWWindowImpl.h"
#include "platform/GLFW_OpenGL_GC.h"
#include "systems/log.h"
/** \file GLFWWindowImpl.cpp
*/
namespace Engine {
#ifdef NG_PLATFORM_WINDOWS
	Window* Window::create(const WindowProperties& newprops) {
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

		glfwSetWindowUserPointer(native, static_cast<void*>(&handler)); //Has event handler as void pointer

		glfwSetWindowCloseCallback(native,
			[](GLFWwindow* window) {
				EventHandler* handler = static_cast<EventHandler*>(glfwGetWindowUserPointer(window));
				auto& onclose = handler->getonclosecallback();
				WindowCloseEvent e;
				onclose(e);
			}
		);

		glfwSetWindowSizeCallback(native,
			[](GLFWwindow* window,int newwidth,int newheight) {
				EventHandler* handler = static_cast<EventHandler*>(glfwGetWindowUserPointer(window));
				auto& onresize = handler->getonresizecallback();
				WindowResizeEvent e(newwidth,newheight);
				onresize(e);
			}
		);

		glfwSetKeyCallback(native,
			[](GLFWwindow* window, int keycode, int scancode, int action, int mods) {
				EventHandler* handler = static_cast<EventHandler*>(glfwGetWindowUserPointer(window));
				if (action == GLFW_PRESS) {
					auto& onkeypress = handler->getonkeypressedcallback();
					KeyPressed e(keycode);
					onkeypress(e);
				}
				else if (action == GLFW_REPEAT) {
					auto& onkeypress = handler->getonkeypressedcallback();
					KeyPressed e(keycode);
					onkeypress(e);
				}
				else {
					auto& onkeyreleased = handler->getonkeyreleasedcallback();
					KeyReleased e(keycode);
					onkeyreleased(e);
				}
			}
		);

		m_context.reset(new GLFW_OpenGL_GC(native));
		m_context->init();

	}

	void GLFWWindowImpl::close(){
		glfwDestroyWindow(native);
	}
	
	void GLFWWindowImpl::onupdate(float timestep) {
		glfwPollEvents();
		m_context->swapbuffers();
	}

	void GLFWWindowImpl::setvsync(bool vsync) {
		props.isvsync = vsync;
		if (vsync) {glfwSwapInterval(1);}
		else {glfwSwapInterval(0);}
	}
}
