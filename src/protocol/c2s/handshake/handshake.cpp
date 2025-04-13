#include "handshake.h"
#include <string>

void Handshake::read()
{
    ci.stream.skipHeader();
    protocolVersion = ci.stream.readVInt();
    if (protocolVersion != PROTOCOLVERSION)
    {
        Logger::debug("Protocol version: " + std::to_string(protocolVersion));
        throw std::runtime_error("Incompatible client");
        return;
    }
    serverAddress = ci.stream.readString();
    port = ci.stream.readUnsignedShort();
    ci.nextState = (State)ci.stream.readVInt();
}

void Handshake::write()
{
    ci.stream.writeVInt(protocolVersion);
    ci.stream.writeString(serverAddress);
    ci.stream.writeUnsignedShort(port);
    ci.stream.writeVInt(ci.nextState);
    ci.stream.writePacketHeader(getPacketID());
}

uint16_t Handshake::getPacketID()
{
    return 0x0;
}