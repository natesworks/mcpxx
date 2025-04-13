#include "handshake.h"
#include <string>

void Handshake::read()
{
    ci.protocolVersion = ci.stream.readVInt();
    if (ci.protocolVersion != PROTOCOLVERSION)
    {
        Logger::debug("Protocol version: " + std::to_string(ci.protocolVersion));
        throw std::runtime_error("Incompatible client");
        return;
    }
    ci.serverAddress = ci.stream.readString();
    ci.port = ci.stream.readUnsignedShort();
    ci.nextState = (State)ci.stream.readVInt();
}

void Handshake::write()
{
    ci.stream.writeVInt(protocolVersion);
    ci.stream.writeString(serverAddress);
    ci.stream.writeUnsignedShort(port);
    ci.stream.writeVInt(nextState);
    ci.stream.writePacketHeader(getPacketID());
}

uint16_t Handshake::getPacketID()
{
    return 0x0;
}