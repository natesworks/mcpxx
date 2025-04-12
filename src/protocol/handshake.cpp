#include "handshake.h"

void Handshake::handlePacket(CallingInstance &ci)
{
    Bytestream stream(ci.data);
    Logger::debug("ci.data.size(): " + std::to_string(ci.data.size()));
    Logger::debug("Offset: " + std::to_string(stream.getOffset()));
    ci.protocolVersion = stream.readVInt();
    Logger::debug("Protocol version: " + std::to_string(ci.protocolVersion));
    if (ci.protocolVersion != PROTOCOLVERSION)
    {
        throw std::runtime_error("Incompatible client");
        return;
    }
    ci.serverAddress = stream.readString();
    ci.port = stream.readUnsignedShort();
    ci.nextState = (State)stream.readVInt();
}