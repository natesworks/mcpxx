#pragma once

#include <string>

#include "../../../core/bytestream.h"
#include "../../../core/server.h"
#include "../../../data/callinginstance.h"
#include "../../../data/packet.h"

class Handshake : public Packet
{
public:
	Handshake(CallingInstance &ci) : Packet(ci), ci(ci) { };
	uint32_t protocolVersion;
	std::string serverAddress;
	uint16_t port;

	void read() override;
	void write() override;
	uint16_t getPacketID() override;

private:
	CallingInstance &ci;
};