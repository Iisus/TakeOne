#pragma once

#include <iostream>

//TODO: Implement Logging

#if ENABLE_DEBUG
	#define LOG_MSG(msg, ...) std::cout << "Not Implemented" << std::endl;
#else
	#define LOG_MSG(...)
#endif