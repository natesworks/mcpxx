#pragma once

#include <vector>

#include "../data/callinginstance.h"
#include "logger.h"
#include "../data/messages.h"

class Messaging
{
public:
    static void handlePacket(CallingInstance &ci);
    static void sendPacket(CallingInstance &ci);
};