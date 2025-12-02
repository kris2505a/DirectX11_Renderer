#pragma once
#include <chrono>

class Clock {
public:
	Clock() {
		m_prevTime = std::chrono::high_resolution_clock::now();
		m_currTime = std::chrono::high_resolution_clock::now();
	}

	float elapsed() {
		m_currTime = std::chrono::high_resolution_clock::now();
		std::chrono::duration <float> elapsed = m_prevTime - m_currTime;
		m_prevTime = m_currTime;
		return elapsed.count();
	}
	~Clock() = default;

private:
	std::chrono::high_resolution_clock::time_point m_prevTime;
	std::chrono::high_resolution_clock::time_point m_currTime;
};