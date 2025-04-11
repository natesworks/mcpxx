#include "messaging.h"

void Messaging::handlePacket(CallingInstance &ci) // TODO remove this and make this a custom function that you can specify in server ("handler")
{
    if (ci.state == Handshaking && ci.packetID == 0x0)
    {
        Handshake::handlePacket(ci);
    }
}