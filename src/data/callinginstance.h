#pragma once

#include <cstdint>
#include <vector>

#include "player.h"
#include "state.h"
#include "type.h"
#include "../core/bytestream.h"

class CallingInstance
{
public:
	CallingInstance(Type type) : type(type) {}

	int socket;
	Player player;
	uint16_t packetID;
	std::vector<uint8_t> data;
	uint32_t packetLength;
	const Type type;

	uint32_t protocolVersion;
	std::string serverAddress;
	uint16_t port;

	State state;
	State nextState; // Edit this instead of state or else handlers will break!
	Bytestream stream;
};