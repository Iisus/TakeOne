#pragma once

#include <iostream>

//TODO: Implement better Logging system (with levels)

#if ENABLE_DEBUG
	#define LOG_MSG(...) printf("\n(%s:%d) - ", __FILE__, __LINE__); printf(__VA_ARGS__);
#else
	#define LOG_MSG(...)
#endif
