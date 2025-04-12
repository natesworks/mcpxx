#include "messaging.h"
#include <mcpxx/data/state.h>

void Messaging::handlePacket(CallingInstance &ci) // TODO remove this and make this a custom function that you can specify in server ("handler")
{
    if (ci.state == Handshaking && ci.packetID == 0x00)
    {
        Handshake::handlePacket(ci);
    }
}

void Messaging::sendPacket(CallingInstance &ci)
{

}