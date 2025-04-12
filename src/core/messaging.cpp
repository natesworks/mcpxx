#include "messaging.h"
#include "../data/state.h"

void Messaging::handlePacket(CallingInstance &ci) // TODO remove this and make this a custom function that you can specify in server ("handler")
{
    Logger::debug("Handling packet: " + std::to_string(ci.packetID) + " in state: " + std::to_string(ci.state));
    if (ci.state == Handshaking && ci.packetID == 0x00)
    {
        Handshake::handlePacket(ci);
    }
}

void Messaging::sendPacket(CallingInstance &ci)
{

}