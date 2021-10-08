#include "engine_pch.h"
#include "systems/log.h"

namespace Engine {
	std::shared_ptr <spdlog::logger> Log::consolelogger = nullptr;
	void Log::start(SystemSignal init, ...) {
		spdlog::set_pattern("%^[%T]:%v%$");
		spdlog::set_level(spdlog::level::trace);
		consolelogger = spdlog::stderr_color_mt("console");
	}

	void Log::stop(SystemSignal init, ...) {
		consolelogger->info("stopping");
		consolelogger.reset();
	}
}