#include "messaging.h"
#include "../data/state.h"

void Messaging::handlePacket(CallingInstance &ci)
{
    Logger::debug("Handling packet: " + Utilities::toHex(ci.packetID) + " in state: " + std::to_string(ci.state));
    ci.stream = Bytestream(ci.data);
    ci.stream.skipHeader();

    if (ci.type == ServerType)
    {
        if (ci.state == Handshaking)
        {
            if (ci.packetID == 0x0)
            {
                Handshake handshake(ci);
                handshake.read();
            }
        }
        else if (ci.state == Status)
        {
            if (ci.packetID == 0x00)
            {

            }
        }
    }
    else if (ci.type == ClientType)
    {

    }

    /* If any data was written; send it */
    if (ci.stream.getOffset() != 0)
    {
        send(ci.socket, ci.stream.getBuffer().data(), ci.stream.getBuffer().size(), 0);
    }
}

void Messaging::sendPacket(CallingInstance &ci)
{

}