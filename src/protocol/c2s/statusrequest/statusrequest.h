#pragma once

#include "../../../data/packet.h"
#include "../../../core/bytestream.h"
#include "../../../data/callinginstance.h"
#include "../../../core/server.h"

class StatusRequest : public Packet
{
public:
	StatusRequest(CallingInstance &ci) : Packet(ci), ci(ci) { };

	void read() override;
	void write() override;
	uint16_t getPacketID() override;

private:
	CallingInstance &ci;
};