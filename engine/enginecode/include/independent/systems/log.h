#pragma once
#include "systems/system.h"
#include "spdlog/spdlog.h"

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
	private:
		static std::shared_ptr<spdlog::logger> consolelogger;
	};

	template<class ...Args>
	static void Log::debug(Args&&...args) {
		consolelogger->debug(std::forward<Args>(args))
	}

	template<class ...Args>
	static void Log::error(Args&&...args) {
		consolelogger->debug(std::forward<Args>(args))
	}

	template<class ...Args>
	static void Log::info(Args&&...args) {
		consolelogger->debug(std::forward<Args>(args))
	}

	template<class ...Args>
	static void Log::trace(Args&&...args) {
		consolelogger->debug(std::forward<Args>(args))
	}

	template<class ...Args>
	static void Log::warn(Args&&...args) {
		consolelogger->debug(std::forward<Args>(args))
	}

}