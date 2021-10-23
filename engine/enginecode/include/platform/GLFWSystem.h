#pragma once

#include "systems/system.h"
#include <GLFW/glfw3.h>
#include "systems/log.h"
namespace Engine {
	class GLFWSystem : public System {
		virtual void start(SystemSignal init = SystemSignal::None, ...) override {
			auto errorcode = glfwInit();
			if (!errorcode) {
				Log::error("cannot init glfw {0}", errorcode);
			}
		}

		virtual void stop(SystemSignal close = SystemSignal::None, ...) override {
			glfwTerminate();
		}
	};
}