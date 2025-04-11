#pragma once

#include "../core/bytestream.h"
#include "../data/callinginstance.h"
#include "../core/server.h"

class Handshake
{
public:
    static void handlePacket(CallingInstance &ci);
};