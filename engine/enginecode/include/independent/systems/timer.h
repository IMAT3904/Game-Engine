#pragma once
#include <chrono>

namespace Engine {
	class Timer {
	public:
		virtual void start() = 0;
		virtual void reset() = 0;
		virtual float getelapsedtime() = 0;
	};

	class ChronoTimer : public Timer{
	public:
		virtual inline void start() override { startpoint = std::chrono::high_resolution_clock::now(); }
		virtual inline void reset() override { startpoint = std::chrono::high_resolution_clock::now(); }
		virtual float getelapsedtime() override{
			endpoint = std::chrono::high_resolution_clock::now();
			std::chrono::duration<float, std::milli> elapsed = endpoint - startpoint;
			return elapsed.count() / 1000.f;
		}
	private:
		std::chrono::time_point<std::chrono::high_resolution_clock> startpoint;
		std::chrono::time_point<std::chrono::high_resolution_clock> endpoint;
	};
}