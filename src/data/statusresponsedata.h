#pragma once

#include <string>
#include <vector>
#include <map>
#include <cstdint>

struct StatusResponseData
{
    std::string version;
    std::string protocolVersion;
    int32_t onlinePlayers;
    int32_t maxPlayers;
    std::vector<std::map<std::string, std::string>> players;
    std::string description;
    // TODO favicon
    bool enforcesSecureChat; 
};