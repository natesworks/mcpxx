#include "logger.h"

#include <iostream>

void Logger::log(std::string message)
{
    std::cout << COLOR_LOG << "[INFO] " << RESET << message << std::endl;
}

void Logger::warn(std::string message)
{
    std::cout << COLOR_WARN << "[WARNING] " << RESET << message << std::endl;
}

void Logger::error(std::string message)
{
    std::cerr << COLOR_ERROR << "[ERROR] " << RESET << message << std::endl;
    throw std::runtime_error(message);
}

void Logger::debug(std::string message)
{
    std::cout << COLOR_DEBUG << "[DEBUG] " << RESET << message << std::endl;
}