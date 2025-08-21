#pragma once
#include <MiraEngine/Core/MiraCore.h>
#include <chrono>
#include <string>


#ifdef API_ENGINE
	#define MIRA_LOG(TYPE, ... ) Log::logEngineMessage(TYPE, std::format(__VA_ARGS__))
#else
	#define MIRA_LOG(TYPE, ... ) Log::logMessage(TYPE, std::format(__VA_ARGS__))
#endif


#define INFO 0
#define DEBUG 1
#define WARN 2
#define ERROR 3


class Log {

public:
	Log() = delete;               
	~Log() = delete;              
	Log(const Log&) = delete;     
	Log& operator=(const Log&) = delete;


	static MIRA_API void logTime();
	static MIRA_API void logMessage(int type, const std::string& message);
	static MIRA_API void logEngineMessage(int type, const std::string& message);

private:
	static std::time_t m_now;
	static std::tm m_localTime;
	static std::vector<std::string> m_logColors;

};