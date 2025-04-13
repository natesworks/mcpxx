#pragma once

#include <vector>

#include "../data/callinginstance.h"
#include "logger.h"
#include "../data/packet.h"
#include "../data/messages.h"
#include "../utilities/utilities.h"

class Messaging
{
public:
    static std::unique_ptr<Packet> handlePacket(CallingInstance &ci);
};