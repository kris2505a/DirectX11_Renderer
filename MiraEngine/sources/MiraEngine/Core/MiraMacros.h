#pragma once
#include <MiraEngine/Logging/Log.h>

#define BIT(x) (1 << x)

#define MIRA_ASSERT(x, msg) \
	if(!(x)) { \
		MIRA_LOG(ERROR, msg); \
		std::abort(); } 
		