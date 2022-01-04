#pragma once
#include "systems/system.h"
#include "spdlog/spdlog.h"

/** \file log.h
*/

namespace	Engine {
	/** \class Log
** \brief A static class that can be used for logging to the console


**/
	class Log : public System {
	public:
		virtual void start(SystemSignal init = SystemSignal::None, ...); //!< Start the logger
		virtual void stop(SystemSignal close = SystemSignal::None, ...); //!< Close the logger

		template <class ...Args>
		static void info(Args&& ...args); //!< Create an info log

		template <class ...Args>
		static void error(Args&& ...args); //!< Create an error log

		template <class ...Args>
		static void warn(Args&& ...args); //!< Create an warn log

		template <class ...Args>
		static void trace(Args&& ...args); //!< Create an trace log

		template <class ...Args>
		static void debug(Args&& ...args); //!< Create a debug log

		template <class ...Args>
		static void file(Args&& ...args); //!< Store logs into a file
	private:
		static std::shared_ptr<spdlog::logger> consolelogger; //!< a log to console
		static std::shared_ptr<spdlog::logger> filelogger; //!< a log output to a file
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