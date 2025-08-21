#pragma once

#ifdef API_ENGINE
	#define MIRA_API __declspec(dllexport)
#else
	#define MIRA_API __declspec(dllimport)
#endif // API_ENGINE

