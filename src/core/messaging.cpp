#include "messaging.h"
#include "../data/state.h"
#include "logger.h"

std::unique_ptr<Packet> Messaging::handlePacket(CallingInstance &ci)
{
    Logger::debug("Handling packet: " + Utilities::toHex(ci.packetID) + " in state: " + std::to_string(ci.state));
    ci.stream = Bytestream(ci.data);

    if (ci.type == ServerType)
    {
        if (ci.state == Handshaking)
        {
            if (ci.packetID == 0x0)
            {
                std::unique_ptr<Packet> handshake = std::make_unique<Handshake>(ci);
                handshake->read();
                return handshake;
            }
        }
        else if (ci.state == Status)
        {
            if (ci.packetID == 0x00)
            {
                std::unique_ptr<Packet> statusRequest = std::make_unique<StatusRequest>(ci);
                statusRequest->read();
                return statusRequest;
            }
        }
    }
    else if (ci.type == ClientType)
    {

    }

    return nullptr;
}