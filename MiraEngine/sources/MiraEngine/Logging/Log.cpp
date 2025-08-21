#include <MiraPreCompHeader.h>
#include "Log.h"


std::time_t Log::m_now = std::time(nullptr);
std::tm Log::m_localTime = {};
std::vector<std::string> Log::m_logColors = std::vector<std::string>{ 
												"\033[37m",			//white 
												"\033[33m",			//yellow
												"\033[38;5;208m",	//orange
												"\033[31m",			//red
												"\033[0m"			//reset
											};

void Log::logTime() {
	m_now = std::time(nullptr);
	localtime_s(&m_localTime, &m_now);
	std::cout << "[" << std::put_time(&m_localTime, "%H:%M:%S") << "]: ";
}

void Log::logMessage(int type, const std::string& message) {
	std::cout << m_logColors[type];
	logTime();
	std::cout << "Game ->> " << message << m_logColors[4] << std::endl;
}

void Log::logEngineMessage(int type, const std::string& message) {
	std::cout << m_logColors[type];
	logTime();
	std::cout << "Engine ->> " << message << m_logColors[4] << std::endl;
}





