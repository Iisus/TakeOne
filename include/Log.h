#pragma once

#include <iostream>

#define ENABLE_DEBUG 1

#if ENABLE_DEBUG
	#define LOG_MSG(msg, ...) std::cout << "TODO: Implement Logging" << std::endl;
#else
	#define LOG_MSG(...)
#endif