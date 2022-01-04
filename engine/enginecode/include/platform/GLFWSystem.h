#pragma once

#include "systems/system.h"
#include <GLFW/glfw3.h>
#include "systems/log.h"

/** \file GLFWSystem.h
*/

namespace Engine {
	/** \class GLFWSystem
** \brief A GLFW based class that uses System


**/
	class GLFWSystem : public System {
		virtual void start(SystemSignal init = SystemSignal::None, ...) override { //!< start the system
			auto errorcode = glfwInit();
			if (!errorcode) {
				Log::error("cannot init glfw {0}", errorcode);
			}
		}

		virtual void stop(SystemSignal close = SystemSignal::None, ...) override { //!< stop the system
			glfwTerminate();
		}
	};
}