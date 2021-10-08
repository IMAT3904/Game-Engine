#include "engine_pch.h"
#include "systems/log.h"

namespace Engine {
	std::shared_ptr <spdlog::logger> Log::consolelogger = nullptr;

	void Log::start(SystemSignal init, ...) {
		spdlog::set_pattern("%^[%T]:%v%$");
		spdlog::set_level(spdlog::level::trace);
		consolelogger = spdlog::stderr_color_mt("Console");
	}

	void Log::stop(SystemSignal close, ...) {
		consolelogger->info("stopping");
		consolelogger.reset();
	}


}