#pragma once
#include "systems/system.h"

namespace	Engine {
	class Log : public System {
	public: 
		virtual void start(SystemSignal init = SystemSignal::None, ...);
		virtual void stop(SystemSignal close = SystemSignal::None, ...);

		template <class ...Args>
		static void info(Args&&...args);

		template <class ...Args>
		static void error(Args&&...args);

		template <class ...Args>
		static void warn(Args&&...args);

		template <class ...Args>
		static void trace(Args&&...args);

		template <class ...Args>
		static void debug(Args&&...args);
	};
}