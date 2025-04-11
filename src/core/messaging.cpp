#include "messaging.h"

void Messaging::handlePacket(CallingInstance &ci)
{
    if (ci.state == Handshaking && ci.packetID == 0x0)
    {
        Handshake::handlePacket(ci);
    }
}