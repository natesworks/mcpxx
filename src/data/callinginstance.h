#pragma once

#include <cstdint>
#include <vector>

#include "player.h"
#include "state.h"

struct CallingInstance
{
	int socket;
	Player player;
	int packetID;
	std::vector<uint8_t> data;
	State state;
};