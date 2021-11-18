#pragma once
#include <chrono>

namespace Engine {
	class ChronoTimer {
	public:
		inline void start() { startpoint = std::chrono::high_resolution_clock::now(); }
		inline void reset() { startpoint = std::chrono::high_resolution_clock::now(); }
		float getelapsedtime() {
			endpoint = std::chrono::high_resolution_clock::now();
			std::chrono::duration<float, std::milli> elapsed = endpoint - startpoint;
			return elapsed.count() / 1000.f;
		}
	private:
		std::chrono::time_point<std::chrono::high_resolution_clock> startpoint;
		std::chrono::time_point<std::chrono::high_resolution_clock> endpoint;
	};
}