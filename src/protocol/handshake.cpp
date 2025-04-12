#include "handshake.h"

void Handshake::handlePacket(CallingInstance &ci)
{
    Bytestream stream(ci.data);
    ci.protocolVersion = stream.readVInt();
    Logger::debug("Protocol version: " + std::to_string(ci.protocolVersion));
    if (ci.protocolVersion != PROTOCOLVERSION)
    {
        throw std::runtime_error("Incompatible client");
        return;
    }
    ci.serverAddress = stream.readString();
    ci.port = stream.readUnsignedShort();
    ci.state = (State)stream.readVInt();
}