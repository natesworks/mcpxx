#pragma once

#include <iostream>
#include <stdexcept>

#include "server.h"

#define COLOR_LOG "\033[34m"
#define COLOR_ERROR "\033[31m"
#define COLOR_WARN "\033[33m"
#define COLOR_DEBUG "\033[32m"
#define RESET "\033[0m"

class Logger
{
public:
	template <typename T>
	static void log(T message)
	{
		std::cout << COLOR_LOG << "[INFO] " << RESET << message << std::endl;
	}

	template <typename T>
	static void warn(T message)
	{
		std::cout << COLOR_WARN << "[WARNING] " << RESET << message << std::endl;
	}

	template <typename T>
	static void error(T message)
	{
		std::cerr << COLOR_ERROR << "[ERROR] " << RESET << message << std::endl;
		throw std::runtime_error(message);
	}

	template <typename T>
	static void debug(T message)
	{
		#ifdef DEBUG
		std::cout << COLOR_DEBUG << "[DEBUG] " << RESET << message << std::endl;
		#endif
	}
};
