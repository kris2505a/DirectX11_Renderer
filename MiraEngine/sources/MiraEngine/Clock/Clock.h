#pragma once
#include <MiraEngine/Core/MiraCore.h>
#include <chrono>


namespace Mira {

class MIRA_API Clock {
public:
	using ClockVar = std::chrono::high_resolution_clock;
	using TimePoint = std::chrono::time_point<ClockVar>;


	Clock() {
		m_start = ClockVar::now();
	}


	inline float restart() {
		auto now = ClockVar::now();
		std::chrono::duration<float> duration = now - m_start;
		m_start = now;
		return duration.count();
	}

	inline float getElapsed() const {
		auto now = ClockVar::now();
		std::chrono::duration<float> duration = now - m_start;
		return duration.count();
	}


private:
	TimePoint m_start;

};

}