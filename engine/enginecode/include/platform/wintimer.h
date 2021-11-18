#pragma once
#include "include/platform/window.h"
#include "include/independent/systems/timer.h"
#include <winnt.h>
#include <profileapi.h>

namespace Engine{
	class WinTimer : public Timer {
	public:
		virtual void start() override {
			QueryPerformanceFrequency(&frequency);
			QueryPerformanceCounter(&startpoint);
		};
		virtual void reset() override { QueryPerformanceCounter(&startpoint); };
		virtual float getelapsedtime() override {
			QueryPerformanceCounter(&endpoint);
			float result = (endpoint.QuadPart - startpoint.QuadPart) * 1000.0 / frequency.QuadPart;
			result /= 1000.f;
			return result;
		};
	private:
		LARGE_INTEGER startpoint;
		LARGE_INTEGER endpoint;
		LARGE_INTEGER frequency;
	};
}