#pragma once

#include <vector>

#include "../data/callinginstance.h"
#include "logger.h"

class Messaging
{
public:
    static void handlePacket(CallingInstance &ci);
    static void sendPacket(int packetID, const std::vector<uint8_t> &data, CallingInstance &ci);
};