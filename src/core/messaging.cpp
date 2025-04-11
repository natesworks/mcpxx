#include "messaging.h"

void Messaging::handlePacket(int packetID, const std::vector<uint8_t> &data, CallingInstance &ci)
{
    switch (packetID)
    {
        default:
            Logger::warn("Unknown packet ID: " + std::to_string(packetID));
            break;
    }
}