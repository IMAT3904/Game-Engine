#include "engine_pch.h"
#include "systems/log.h"

namespace Engine {
	std::shared_ptr <spdlog::logger> Log::consolelogger = nullptr;
	std::shared_ptr <spdlog::logger> Log::filelogger = nullptr;

	void Log::start(SystemSignal init, ...) {
		spdlog::set_pattern("%^[%T]:%v%$");
		spdlog::set_level(spdlog::level::trace);
		consolelogger = spdlog::stderr_color_mt("Console");

		char filepath[256] = "logs/";
		char time[128];
		std::time_t t = std::time(nullptr);
		std::strftime(time, sizeof(time), "%d_%m_%y %I_%M_%S", std::localtime(&t));
		strcat_s(filepath, time);
		strcat_s(filepath,".txt");

		filelogger = spdlog::basic_logger_mt("File", filepath);
	}

	void Log::stop(SystemSignal close, ...) {
		consolelogger->info("stopping");
		consolelogger.reset();
	}


}