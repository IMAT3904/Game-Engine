#pragma once
#include <chrono>

/** \file timer.h
*/

namespace Engine {
	/** \class Timer
** \brief A pure virtual timer class to keep track of the time


**/
	class Timer {
	public:
		virtual void start() = 0; //!< Start the timer
		virtual void reset() = 0; //!< Reset the timer
		virtual float getelapsedtime() = 0; //!< Get the elapsed time
	};

	/** \class ChronoTimer
** \brief A class to override timer 


**/

	class ChronoTimer : public Timer{
	public:
		virtual inline void start() override { startpoint = std::chrono::high_resolution_clock::now(); } //!< Start the timer
		virtual inline void reset() override { startpoint = std::chrono::high_resolution_clock::now(); } //!< Reset the timer
		virtual float getelapsedtime() override{ //!< Get the elapsed time
			endpoint = std::chrono::high_resolution_clock::now();
			std::chrono::duration<float, std::milli> elapsed = endpoint - startpoint;
			return elapsed.count() / 1000.f;
		}
	private:
		std::chrono::time_point<std::chrono::high_resolution_clock> startpoint; //!< The start point of the timer
		std::chrono::time_point<std::chrono::high_resolution_clock> endpoint; //!< The end point of the timer
	};
}