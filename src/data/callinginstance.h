#pragma once

#include <cstdint>
#include <vector>

#include "player.h"
#include "state.h"

struct CallingInstance
{
public:
	int socket;
	Player player;
	uint32_t packetID;
	std::vector<uint8_t> data;
	uint32_t packetLength;

	uint32_t protocolVersion;
	std::string serverAddress;
	ushort port;

	State state;
	State nextState; // Edit this instead of state or else handlers will break!
};