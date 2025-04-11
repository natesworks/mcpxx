#pragma once

#include <string>

#define COLOR_LOG "\033[34m"
#define COLOR_ERROR "\033[31m"
#define COLOR_WARN "\033[33m"
#define COLOR_DEBUG "\033[32m"
#define RESET "\033[0m"

class Logger
{
public:
	static void log(std::string message);
	static void warn(std::string message);
	static void error(std::string message);
	static void debug(std::string message);
};