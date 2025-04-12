#include "handshake.h"

void Handshake::handlePacket(CallingInstance &ci)
{
    Bytestream stream(ci.data);
    ci.protocolVersion = stream.readVInt();
    if (ci.protocolVersion != PROTOCOLVERSION)
    {
        throw std::runtime_error("Incompatible client");
        return;
    }
    ci.serverAddress = stream.readString();
    ci.port = stream.readUnsignedShort();
    ci.state = (State)stream.readVInt();
}