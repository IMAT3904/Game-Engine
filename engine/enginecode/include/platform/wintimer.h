#pragma once
#include "include/platform/window.h"
#include "include/independent/systems/timer.h"
#include <winnt.h>
#include <profileapi.h>

/** \file wintimer.h
*/

namespace Engine{
	/** \class WinTimer
** \brief A Windows timer that overrides Timer


**/
	class WinTimer : public Timer {
	public:
		virtual void start() override { //!< start the timer
			QueryPerformanceFrequency(&frequency);
			QueryPerformanceCounter(&startpoint);
		};
		virtual void reset() override { QueryPerformanceCounter(&startpoint); }; //!< reset the timer
		virtual float getelapsedtime() override { //!< get the elapsed timer
			QueryPerformanceCounter(&endpoint);
			float result = (endpoint.QuadPart - startpoint.QuadPart) * 1000.0 / frequency.QuadPart;
			result /= 1000.f;
			return result;
		};
	private:
		LARGE_INTEGER startpoint; //!< start point
		LARGE_INTEGER endpoint; //!< end point
		LARGE_INTEGER frequency; //!< frequency
	};
}