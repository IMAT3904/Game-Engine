#pragma once
#include "systems/system.h"
#include "spdlog/spdlog.h"

namespace	Engine {
	class Log : public System {
	public:
		virtual void start(SystemSignal init = SystemSignal::None, ...);
		virtual void stop(SystemSignal close = SystemSignal::None, ...);

		template <class ...Args>
		static void info(Args&& ...args);

		template <class ...Args>
		static void error(Args&& ...args);

		template <class ...Args>
		static void warn(Args&& ...args);

		template <class ...Args>
		static void trace(Args&& ...args);

		template <class ...Args>
		static void debug(Args&& ...args);

		template <class ...Args>
		static void file(Args&& ...args);
	private:
		static std::shared_ptr<spdlog::logger> consolelogger;
		static std::shared_ptr<spdlog::logger> filelogger;
	};

	template<class ...Args>
	static void Log::debug(Args&& ...args) {
		consolelogger->debug(std::forward<Args>(args) ...);
	}

	template<class ...Args>
	static void Log::error(Args&& ...args) {
#ifdef NG_DEBUG
		consolelogger->debug(std::forward<Args>(args) ...);
#endif // NG_DEBUG
	}

	template<class ...Args>
	static void Log::info(Args&& ...args) {
#ifdef NG_DEBUG
		consolelogger->debug(std::forward<Args>(args) ...);
#endif // NG_DEBUG
	}

	template<class ...Args>
	static void Log::trace(Args&& ...args) {
#ifdef NG_DEBUG
		consolelogger->debug(std::forward<Args>(args) ...);
#endif // NG_DEBUG
	}

	template<class ...Args>
	static void Log::warn(Args&& ...args) {
#ifdef NG_DEBUG
		consolelogger->debug(std::forward<Args>(args) ...);
#endif // NG_DEBUG
	}

	template<class ...Args>
	static void Log::file(Args&& ...args) {
		filelogger->trace(std::forward<Args>(args) ...);
	}
}